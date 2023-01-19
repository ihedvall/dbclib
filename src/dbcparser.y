%require "3.2"
%language "c++"

%define api.prefix {dd}
%define api.namespace {dbc}
%define api.parser.class {DbcParser}


%code requires {
    #include "dbc/attribute.h"
    #include "dbc/signal.h"
    namespace dbc {
        class DbcScanner;
    }
}

%parse-param { dbc::DbcScanner &scanner  }

%code  {
    #include <sstream>
    #include "dbcscanner.h"
    #include <limits>

    #undef yylex
    #define yylex scanner.ddlex
}

%define api.value.type variant
%token TAG_COLON
%token TAG_SEMICOLON
%token TAG_SEP
%token TAG_AT
%token TAG_PLUS
%token TAG_MINUS
%token TAG_BOX_OPEN
%token TAG_BOX_CLOSE
%token TAG_PAR_OPEN
%token TAG_PAR_CLOSE
%token TAG_COMMA
%token TAG_VERSION
%token TAG_BO         /* Botschaft */
%token TAG_BS
%token TAG_BU         /* Steuergerät */
%token TAG_SG         /* Signal */
%token TAG_EV         /* Environment */
%token TAG_NS
%token TAG_NS_DESC
%token TAG_CM         /* Comment */
%token TAG_BA_DEF     /* Attribut-Definition */
%token TAG_BA         /* Attribut */
%token TAG_VAL
%token TAG_CAT_DEF
%token TAG_CAT
%token TAG_FILTER
%token TAG_BA_DEF_DEF
%token TAG_EV_DATA
%token TAG_ENVVAR_DATA
%token TAG_SGTYPE
%token TAG_SGTYPE_VAL
%token TAG_BA_DEF_SGTYPE
%token TAG_BA_SGTYPE
%token TAG_SIG_TYPE_REF
%token TAG_VAL_TABLE
%token TAG_SIG_GROUP
%token TAG_SIG_VALTYPE
%token TAG_SIGTYPE_VALTYPE
%token TAG_BO_TX_BU
%token TAG_BA_DEF_REL
%token TAG_BA_REL
%token TAG_BA_DEF_DEF_REL
%token TAG_BU_SG_REL
%token TAG_BU_EV_REL
%token TAG_BU_BO_REL
%token TAG_SG_MUL_VAL
%token TAG_NAN
%token TAG_INT
%token TAG_FLOAT
%token TAG_ENUM
%token TAG_HEX
%token TAG_STRING

%token <int> TAG_DUMMY_NODE_VECTOR
%token <std::string> ID_VAL
%token <std::string> STRING_VAL
%token <int64_t>     INT_VAL
%token <double>      DOUBLE_VAL
%token <int>         ENUM_VAL
%token <uint64_t>    HEX_VAL
%token EOL 0

%nterm <std::string> attribute_value
%nterm <double> double_val
%nterm <AttributeType> object_type
%nterm <AttributeType> object_rel_type
%nterm <AttributeType> attribute_object_type
%nterm <bool> attribute_definition_object_or_relation
%nterm <std::string> mux_info
%nterm <bool> little_endian
%nterm <SignalDataType> signedness

%right TAG_NS_DESC TAG_CM
%start dbc_file
%%

dbc_file: dbc_key_list;

dbc_key_list: %empty
    | dbc_key_list dbc_key;

dbc_key:
    version
    | symbol_section
    | bus_speed
	| node
	| valtable
    | message_list
    | message_transmitters
    | envvar
    | envvar_data
    | comment_tag
    | attribute_definition
    | attribute_definition_default
    | attribute
	| attribute_rel
    | val
	| category_definition
	| category
    | signal_group
    | sig_valtype
    | extended_mux;

version:
	TAG_VERSION STRING_VAL
	{
	    auto& network = scanner.GetNetwork();
		network.Version($2);
		scanner.ResetTempList();
	};

symbol_section:
    TAG_NS TAG_COLON symbol_list;

symbol_list: %empty
    | symbol symbol_list ;

symbol:  TAG_NS_DESC
    | TAG_CM
    | TAG_BA_DEF
    | TAG_BA
    | TAG_VAL
    | TAG_EV
    | TAG_CAT_DEF
    | TAG_CAT
    | TAG_FILTER
    | TAG_BA_DEF_DEF
    | TAG_EV_DATA
    | TAG_ENVVAR_DATA
    | TAG_SGTYPE
    | TAG_SGTYPE_VAL
    | TAG_BA_DEF_SGTYPE
    | TAG_BA_SGTYPE
    | TAG_SIG_TYPE_REF
    | TAG_VAL_TABLE
    | TAG_SIG_GROUP
    | TAG_SIG_VALTYPE
    | TAG_SIGTYPE_VALTYPE
    | TAG_BO_TX_BU
    | TAG_BA_DEF_REL
    | TAG_BA_REL
    | TAG_BA_DEF_DEF_REL
    | TAG_BU_SG_REL
    | TAG_BU_EV_REL
    | TAG_BU_BO_REL
    | TAG_SG_MUL_VAL
    ;

envvar:
      TAG_EV                    /* EV_               */
      ID_VAL                    /*  2: environment variable name */
      TAG_COLON                 /* :                 */
      INT_VAL                   /*  4: type: 0 int, 1 float, 0 string, 0 data */
      TAG_BOX_OPEN              /* [                 */
      double_val                /*  6: minimum value */
      TAG_SEP                   /* |                 */
      double_val                /*  8: maximum value */
      TAG_BOX_CLOSE             /* ]                 */
      STRING_VAL                /* 10: unit          */
      double_val                /* 11: initial value */
      INT_VAL                   /* 12: ev_id UINT obsolete  */
      TAG_DUMMY_NODE_VECTOR     /* 13: access type   */
      comma_identifier_list     /* 14: node list     */
      TAG_SEMICOLON
    {
        auto& network = scanner.GetNetwork();
        auto& env_var = network.GetEnvVar($2);
        env_var.Type(static_cast<EnvType>($4));
        env_var.Min( $6 );
        env_var.Max( $8 );
        env_var.Unit( $10 );
        env_var.InitValue($11);
        env_var.Ident(static_cast<uint64_t>($12));
        env_var.Access(static_cast<AccessType>($13));
        const auto& list = scanner.StringList();
        env_var.NodeList(list);
        scanner.ResetTempList();
    };

envvar_data:
      TAG_ENVVAR_DATA ID_VAL /* environment variable name */
      TAG_COLON INT_VAL  /* length (data) */
      TAG_SEMICOLON
	  {
		/* To be defined what to do here */
		scanner.ResetTempList();
	  };

category_definition:
	TAG_CAT_DEF INT_VAL ID_VAL INT_VAL TAG_SEMICOLON ;

category:
	  TAG_CAT TAG_BU ID_VAL INT_VAL TAG_SEMICOLON
	| TAG_CAT TAG_BO INT_VAL INT_VAL TAG_SEMICOLON;


attribute_value:
     INT_VAL     { $$ = std::to_string($1); }
    | STRING_VAL { $$ = $1; }
    | DOUBLE_VAL { $$ = std::to_string($1); };


attribute:
      TAG_BA     /* BA_ (Notwork attributes) */
      STRING_VAL /* Attribute name */
      attribute_value /* Attribute value */
      TAG_SEMICOLON
	  {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition($2);
		auto& attribute = network.CreateAttribute( definition );
		attribute.Value($3);
		scanner.ResetTempList();
	  }
    | TAG_BA /* BA_ (Node attribute) */
      STRING_VAL /* Attribute name */
      TAG_BU /* BU_ */
      ID_VAL /* Node (ECU) name */
      attribute_value /* Value */
      TAG_SEMICOLON
 	  {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition($2);
		auto* node = network.GetNode( $4 );
		if ( node != nullptr) {
			auto& attribute = node->CreateAttribute( definition );
            attribute.Value($5);
		}
		scanner.ResetTempList();
	  }
    | TAG_BA /* Message attribute */
       STRING_VAL /* Attribute name */
       TAG_BO /* BO_ */
       INT_VAL /* Message ID */
       attribute_value /* Value */
       TAG_SEMICOLON
 	  {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition($2);
		auto* message = network.GetMessage( static_cast<uint64_t>($4));
		if ( message != nullptr ) {
			auto& attribute = message->CreateAttribute( definition );
            attribute.Value($5);
		}
		scanner.ResetTempList();
	  }
    | TAG_BA             /* BA_ */
      STRING_VAL     /* attribute name */
      TAG_SG             /* SG_ */
      INT_VAL        /* message id */
      ID_VAL             /* signal name */
      attribute_value  /* attribute value */
      TAG_SEMICOLON      /* ; */
 	  {
		 auto& network = scanner.GetNetwork();
		 auto& definition = network.CreateDefinition($2);
		 auto* signal = network.GetSignal( static_cast<uint64_t>($4), $5);
		 if ( signal != nullptr ) {
		   auto& attribute = signal->CreateAttribute( definition );
           attribute.Value($6);
	     }
	     scanner.ResetTempList();
	  };

attribute_rel:
      /* node-message relational attribute */
      TAG_BA_REL        /* 1 BA_REL_ */
      STRING_VAL    /* 2 attribute name */
      TAG_BU_SG_REL     /* 3 BU_SG_REL */
      ID_VAL        /* 4 node name */
      TAG_SG        /* 5 SG_  */
      INT_VAL       /* 6 message id */
      ID_VAL        /* 7 signal name */
      attribute_value /* 8 attribute value */
      TAG_SEMICOLON     /* 9 ; */
	  {
		/* To be defined */
		scanner.ResetTempList();
	  };

/* set context dependent attribute value type */
attribute_definition_default:
      attribute_definition_object_or_relation STRING_VAL double_val TAG_SEMICOLON
	  {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition( $2 );
		definition.Value( $3 );
		scanner.ResetTempList();
	  }
    | attribute_definition_object_or_relation STRING_VAL STRING_VAL TAG_SEMICOLON
 	  {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition( $2 );
		definition.Value( $3 );
		scanner.ResetTempList();
	  };

attribute_definition_object_or_relation:
      TAG_BA_DEF_DEF  { $$ = false; }
    | TAG_BA_DEF_DEF_REL { $$ = true; };


attribute_definition:
      attribute_object_type STRING_VAL TAG_INT INT_VAL INT_VAL TAG_SEMICOLON
	  {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( $2 );
       	definition.Type( $1 );
       	definition.ValueType( AttributeValueType::IntegerValue);
		definition.Min(static_cast<double>( $4 ));
		definition.Max(static_cast<double>( $5 ));
		scanner.ResetTempList();
	  }
    | attribute_object_type STRING_VAL TAG_FLOAT double_val double_val TAG_SEMICOLON
	  {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( $2 );
       	definition.Type( $1 );
       	definition.ValueType( AttributeValueType::FloatValue);
		definition.Min( $4 );
		definition.Max( $5 );
		scanner.ResetTempList();
	  }
    | attribute_object_type STRING_VAL TAG_STRING TAG_SEMICOLON
	  {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( $2 );
       	definition.Type( $1 );
       	definition.ValueType( AttributeValueType::StringValue);
       	scanner.ResetTempList();
	  }
    | attribute_object_type STRING_VAL TAG_ENUM comma_string_list TAG_SEMICOLON
 	  {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( $2 );
       	definition.Type( $1 );
       	definition.ValueType( AttributeValueType::EnumValue);
       	const auto& list = scanner.StringList();
        definition.EnumList(list);
		scanner.ResetTempList();
	  }
   | attribute_object_type STRING_VAL TAG_HEX INT_VAL INT_VAL TAG_SEMICOLON
 	  {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( $2 );
       	definition.Type( $1 );
       	definition.ValueType( AttributeValueType::HexValue);
		definition.Min(static_cast<double>( $4 ));
		definition.Max(static_cast<double>( $5 ));
		scanner.ResetTempList();
	  };

attribute_object_type:
    TAG_BA_DEF object_type {$$ = $<AttributeType>1;}
    | TAG_BA_DEF_REL object_rel_type {$$ = $<AttributeType>1;};

object_type:
    %empty { $$ = AttributeType::DbcNetwork; }
    | TAG_BU   { $$ = AttributeType::DbcNode; }
    | TAG_BO   { $$ = AttributeType::DbcMessage; }
    | TAG_SG   { $$ = AttributeType::DbcSignal; }
    | TAG_EV   { $$ = AttributeType::EnvironmentVariable; };

object_rel_type:
    TAG_BU_SG_REL { $$ = AttributeType::NodeSignalRelation; }
    | TAG_BU_BO_REL { $$ = AttributeType::NodeMessageRelation; };

val:
    TAG_VAL INT_VAL ID_VAL val_map TAG_SEMICOLON
 	{
	    auto& network = scanner.GetNetwork();
	    auto* signal = network.GetSignal(static_cast<uint64_t>( $2 ), $3);
	    if (signal != nullptr) {
	        const auto& list = scanner.EnumList();
	        signal->EnumList(list);
	    }
	    scanner.ResetTempList();
	}
   /* VAL_ envvarname val_map */
    | TAG_VAL ID_VAL val_map TAG_SEMICOLON
	{
	    auto& network = scanner.GetNetwork();
	    auto& env_var = network.GetEnvVar( $2 );
	    const auto& list = scanner.EnumList();
	    env_var.EnumList(list);
	    scanner.ResetTempList();
	};

val_map:
    %empty
    | val_map_entry val_map
    ;

val_map_entry:
      INT_VAL STRING_VAL
	{
	    scanner.AddToEnumList($1, $2 ); /* Temp storage on network */
	}
    ;

/*
 * set signal value type in target signal
 *
 * SIG_VALTYPE:
 * no section - signed or unsigned
 * 1 - IEEE float
 * 2 - IEEE double
 */
sig_valtype:
      TAG_SIG_VALTYPE INT_VAL ID_VAL TAG_COLON INT_VAL TAG_SEMICOLON
	{
	    auto& network = scanner.GetNetwork();
	    auto* signal = network.GetSignal(static_cast<uint64_t>($2), $3);

	    if (signal != nullptr) {
	        switch ($5) {
	          case 1:
	            signal->DataType(SignalDataType::FloatData);
	            break;

	          case 2:
	            signal->DataType(SignalDataType::DoubleData);
	            break;

	          default:
	            break;
	        }
	    }
	};

comment_tag:
   comment_network
 | comment_node
 | comment_message
 | comment_signal
 | comment_env_var;

comment_network:
    TAG_CM STRING_VAL TAG_SEMICOLON
    {
	  auto& network = scanner.GetNetwork();
	  network.Comment( $2 );
	  scanner.ResetTempList();
    };

comment_node:
    TAG_CM TAG_BU ID_VAL STRING_VAL TAG_SEMICOLON
    {
  	  auto& network = scanner.GetNetwork();
  	  auto* node = network.GetNode( $3 );
  	  if ( node != nullptr ) {
  	    node->Comment( $4 );
  	  }
  	  scanner.ResetTempList();
    };

comment_message:
    TAG_CM TAG_BO INT_VAL STRING_VAL TAG_SEMICOLON
    {
	  auto& network = scanner.GetNetwork();
	  auto* message = network.GetMessage( static_cast<uint64_t>($3));
	  if ( message != nullptr ) {
	    message->Comment( $4 );
	  }
	  scanner.ResetTempList();
    };

comment_signal:
    TAG_CM TAG_SG INT_VAL ID_VAL STRING_VAL TAG_SEMICOLON
    {
 	  auto& network = scanner.GetNetwork();
 	  auto* signal = network.GetSignal( static_cast<uint64_t>($3), $4);
 	  if ( signal != nullptr ) {
 	    signal->Comment( $5 );
 	  }
 	  scanner.ResetTempList();
    };

comment_env_var:
    TAG_CM TAG_EV ID_VAL STRING_VAL TAG_SEMICOLON
    {
	  auto& network = scanner.GetNetwork();
	  auto& env_var = network.GetEnvVar($3);
	  env_var.Comment($4);
	  scanner.ResetTempList();
    };


message_list: message signal_list;

message:
      TAG_BO INT_VAL ID_VAL TAG_COLON INT_VAL ID_VAL
    {
	  auto& network = scanner.GetNetwork();
	  auto& message = network.CreateMessage(static_cast<uint64_t>($2));
	  message.Name($3);
	  message.NofBytes(static_cast<size_t>($5));
	  message.Node($6);
	  scanner.ResetTempList();
    };

signal_list:
      %empty
    | signal_list signal
    ;

signal:
      TAG_SG
      ID_VAL     /* Signal name (within message) */
      mux_info   /* Multiplexing information */
      TAG_COLON
      INT_VAL    /* Bit start */
      TAG_SEP
      INT_VAL    /* Bit length */
      TAG_AT
      little_endian   /* Endian Little = 1 */
      signedness      /* + = Unsigned, - = Signed */
      TAG_PAR_OPEN
      double_val      /* Scale */
      TAG_COMMA
      double_val      /* Offset */
      TAG_PAR_CLOSE
      TAG_BOX_OPEN
      double_val      /* Min */
      TAG_SEP
      double_val      /* Max */
      TAG_BOX_CLOSE
      STRING_VAL      /* Unit */
      comma_identifier_list /* Receivers */
	{
		auto& network = scanner.GetNetwork();
		auto* message = network.LastMessage();
		if (message != nullptr) {
		    auto& signal = message->CreateSignal($2);
		    signal.MessageId(message->Ident()); // Used to find its message later on
		    std::string mux = $3;
		    if (mux.size() > 2 && mux.back() == 'M' && mux.front() == 'm') {
		        // Extended multiplexed value.
		      signal.Mux(MuxType::ExtendedMultiplexor);
		      mux.pop_back(); // So parsing of index works below
   		      signal.MuxValue( std::stoi(mux.substr(1)) );
		    } else if (!mux.empty() && mux[0] == 'M') {
		      signal.Mux(MuxType::Multiplexor);
		      signal.MuxValue(0);
		    } else if (!mux.empty() && mux[0] == 'm') {
		      signal.Mux(MuxType::Multiplexed);
		      signal.MuxValue( std::stoi(mux.substr(1)) );
		    } else {
		      signal.Mux(MuxType::NotMultiplexed);
		      signal.MuxValue(0);
		    }
		    signal.BitStart(static_cast<size_t>($5));
		    signal.BitLength(static_cast<size_t>($7));
		    signal.LittleEndian($9);
		    signal.DataType($10);
		    signal.Scale($12);
		    signal.Offset($14);
		    signal.Min($17);
            signal.Max($19);
            signal.Unit($21);
            const auto& list = scanner.StringList();
            signal.Receivers(list);
		}
		scanner.ResetTempList();
	};

/*********************************************************************/

mux_info:
    %empty
    {
	  $$ = "";
    }
    | ID_VAL
    {
        $$ = $1;
    };

signal_name_list: space_identifier_list;

space_identifier_list:
	   %empty
     | space_identifier_list ID_VAL
	 {
		scanner.AddToStringList( $2 );
	 };

comma_identifier_list:
     %empty
    | ID_VAL
    {
		scanner.AddToStringList( $1 );
    }
    | comma_identifier_list TAG_COMMA ID_VAL
    {
		scanner.AddToStringList( $3 );
    };

comma_string_list:
     STRING_VAL
    {
        scanner.AddToStringList( $1 );
    }
    | comma_string_list TAG_COMMA STRING_VAL
   	{
    	scanner.AddToStringList( $3 );
    }



/* double_val or int_val as float */
double_val:
      DOUBLE_VAL { $$ = $1; }
    | TAG_NAN    { $$ = std::numeric_limits<double>::quiet_NaN(); }
    | INT_VAL    { $$ = static_cast<double>($1); }
    ;

little_endian: INT_VAL { $$ = $1 == 1; };

signedness:
      TAG_PLUS { $$ = SignalDataType::UnsignedData; }
    | TAG_MINUS { $$ = SignalDataType::SignedData; }
    ;

/* list of nodes */

space_node_list:
     %empty
    | space_node_list ID_VAL
{
	scanner.AddToStringList( $2 );
};

node:
    TAG_BU TAG_COLON space_node_list
    {
        auto& network = scanner.GetNetwork();
        const auto& list = scanner.StringList();
        for (const auto& node : list) {
            if (node.empty() || node == "Vector__XXX") {
                continue;
            };
            auto& temp = network.CreateNode(node);
       }
       scanner.ResetTempList();
    };


/* Global value tables are commonly not used */
valtable:
    TAG_VAL_TABLE ID_VAL val_map TAG_SEMICOLON
	{
	    auto& list = scanner.EnumList();
		auto& network = scanner.GetNetwork();
		network.AddValueTable($2, list );
		scanner.ResetTempList();
	};

/* message section (BS_) Bit timing is obsolete but still exists in files */
bus_speed:
	TAG_BS TAG_COLON
	| TAG_BS TAG_COLON INT_VAL TAG_COLON INT_VAL TAG_COMMA INT_VAL;

/* signal group */
signal_group:
  TAG_SIG_GROUP INT_VAL ID_VAL INT_VAL TAG_COLON signal_name_list TAG_SEMICOLON
  {
    auto& network = scanner.GetNetwork();
    SignalGroup temp;
    temp.MessageId(static_cast<uint64_t>($2));
    temp.Name($3);
    temp.Repetition(static_cast<size_t>($4));
    const auto& list = scanner.StringList();
    temp.Signals(list);
    network.AddSignalGroup(temp);
    scanner.ResetTempList();
  };

extended_mux:
    TAG_SG_MUL_VAL      /* SG_MUL_VAL_ */
    INT_VAL             /* Message ID */
    ID_VAL              /* Signal (multiplexed) name */
    ID_VAL              /* Multiplexor signal name */
    value_range_list    /* Multiplexor value range from */
    TAG_SEMICOLON
    {
        auto& network = scanner.GetNetwork();
        auto* signal = network.GetSignal(static_cast<uint64_t>($2), $3);
        if (signal != nullptr) {
            auto& mux = signal->GetExtendedMux();
            mux.multiplexor = $4;
            const auto& list = scanner.RangeList();
            mux.range_list = list;
        }
        scanner.ResetTempList();
    };

value_range_list:
    value_range
    | value_range_list value_range ;

value_range:
    INT_VAL
    INT_VAL /* Is actually '-' INT_VAL (parser fix) */
    {
        const auto low = static_cast<size_t>($1);
        const auto high = static_cast<size_t>(-$2); /* Solves the integer problem) */
        scanner.AddToRangeList(low, high);
    };

message_transmitters: TAG_BO_TX_BU INT_VAL TAG_COLON
                      comma_identifier_list TAG_SEMICOLON
	{
		auto& network = scanner.GetNetwork();
		auto* message = network.GetMessage(static_cast<uint64_t>($2));
		if (message != nullptr) {
		    const auto& list = scanner.StringList();
		    for (const auto& node : list) {
		        message->Node(node);
		    }
		}
		scanner.ResetTempList();
	};

%%


void dbc::DbcParser::error(const std::string& err) {
    const auto line = scanner.lineno();
    const auto column = scanner.YYLeng();
    const std::string near = scanner.YYText();
    std::ostringstream error;
    error << "Parser error: " << err
          << ", Line: " << line
          << ", Column: " << column
          << ", Near: " << near;
    scanner.LastError(error.str());
}
