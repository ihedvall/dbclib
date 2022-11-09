// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "dbcparser.hpp"


// Unqualified %code blocks.
#line 14 "D:/projects/dbclib/src/dbcparser.y"

    #include <sstream>
    #include "dbcscanner.h"
    #undef yylex
    #define yylex scanner.yylex

#line 53 "D:/projects/dbclib/src/dbcparser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "D:/projects/dbclib/src/dbcparser.y"
namespace dbc {
#line 127 "D:/projects/dbclib/src/dbcparser.cpp"

  /// Build a parser object.
  DbcParser::DbcParser (dbc::DbcScanner &scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
  {}

  DbcParser::~DbcParser ()
  {}

  DbcParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  DbcParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.copy< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.copy< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  DbcParser::symbol_kind_type
  DbcParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  DbcParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  DbcParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.move< uint64_t > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  DbcParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  DbcParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  DbcParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  DbcParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  DbcParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  DbcParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  DbcParser::symbol_kind_type
  DbcParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  DbcParser::symbol_kind_type
  DbcParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  DbcParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  DbcParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  DbcParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  DbcParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  DbcParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  DbcParser::symbol_kind_type
  DbcParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  DbcParser::stack_symbol_type::stack_symbol_type ()
  {}

  DbcParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.YY_MOVE_OR_COPY< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  DbcParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.move< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  DbcParser::stack_symbol_type&
  DbcParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.copy< int64_t > (that.value);
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.copy< uint64_t > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  DbcParser::stack_symbol_type&
  DbcParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.move< double > (that.value);
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.move< int > (that.value);
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.move< int64_t > (that.value);
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.move< uint64_t > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  DbcParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  DbcParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  DbcParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  DbcParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  DbcParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  DbcParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  DbcParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  DbcParser::debug_level_type
  DbcParser::debug_level () const
  {
    return yydebug_;
  }

  void
  DbcParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  DbcParser::state_type
  DbcParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  DbcParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  DbcParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  DbcParser::operator() ()
  {
    return parse ();
  }

  int
  DbcParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        yylhs.value.emplace< int64_t > ();
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        yylhs.value.emplace< uint64_t > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 3: // version: TAG_VERSION STRING_VAL
#line 110 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
		network.Version(yystack_[0].value.as < std::string > ());
		scanner.ResetTempList();
	}
#line 760 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 39: // envvar: TAG_EV ID_VAL TAG_COLON INT_VAL TAG_BOX_OPEN double_val TAG_SEP double_val TAG_BOX_CLOSE STRING_VAL double_val INT_VAL TAG_DUMMY_NODE_VECTOR comma_identifier_list TAG_SEMICOLON
#line 178 "D:/projects/dbclib/src/dbcparser.y"
    {
        auto& network = scanner.GetNetwork();
        auto& env_var = network.GetEnvVar(yystack_[13].value.as < std::string > ());
        env_var.Type(static_cast<EnvType>(yystack_[11].value.as < int64_t > ()));
        env_var.Min( yystack_[9].value.as< double > () );
        env_var.Max( yystack_[7].value.as< double > () );
        env_var.Unit( yystack_[5].value.as < std::string > () );
        env_var.InitValue(yystack_[4].value.as< double > ());
        env_var.Ident(static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()));
        env_var.Access(static_cast<AccessType>(yystack_[2].value.as < int > ()));
        const auto& list = scanner.StringList();
        env_var.NodeList(list);
        scanner.ResetTempList();
    }
#line 779 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 42: // envvar_data: TAG_ENVVAR_DATA ID_VAL TAG_COLON INT_VAL TAG_SEMICOLON
#line 201 "D:/projects/dbclib/src/dbcparser.y"
          {
		/* To be defined what to do here */
		scanner.ResetTempList();
	  }
#line 788 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 50: // attribute_value: INT_VAL
#line 222 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as< std::string > () = std::to_string(yystack_[0].value.as < int64_t > ()); }
#line 794 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 51: // attribute_value: STRING_VAL
#line 223 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as< std::string > () = yystack_[0].value.as < std::string > (); }
#line 800 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 52: // attribute_value: DOUBLE_VAL
#line 224 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as< std::string > () = std::to_string(yystack_[0].value.as < double > ()); }
#line 806 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 55: // attribute: TAG_BA STRING_VAL attribute_value TAG_SEMICOLON
#line 237 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition(yystack_[2].value.as < std::string > ());
		auto& attribute = network.CreateAttribute( definition );
		attribute.Value(yystack_[1].value.as< std::string > ());
		scanner.ResetTempList();
	  }
#line 818 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 56: // attribute: TAG_BA STRING_VAL TAG_BU ID_VAL attribute_value TAG_SEMICOLON
#line 250 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition(yystack_[4].value.as < std::string > ());
		auto* node = network.GetNode( yystack_[2].value.as < std::string > () );
		if ( node != nullptr) {
			auto& attribute = node->CreateAttribute( definition );
            attribute.Value(yystack_[1].value.as< std::string > ());
		}
		scanner.ResetTempList();
	  }
#line 833 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 57: // attribute: TAG_BA STRING_VAL TAG_BO INT_VAL attribute_value TAG_SEMICOLON
#line 266 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition(yystack_[4].value.as < std::string > ());
		auto* message = network.GetMessage( static_cast<uint64_t>(yystack_[2].value.as < int64_t > ()));
		if ( message != nullptr ) {
			auto& attribute = message->CreateAttribute( definition );
            attribute.Value(yystack_[1].value.as< std::string > ());
		}
		scanner.ResetTempList();
	  }
#line 848 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 58: // attribute: TAG_BA STRING_VAL TAG_SG INT_VAL ID_VAL attribute_value TAG_SEMICOLON
#line 283 "D:/projects/dbclib/src/dbcparser.y"
          {
		 auto& network = scanner.GetNetwork();
		 auto& definition = network.GetDefinition(yystack_[5].value.as < std::string > ());
		 auto* signal = network.GetSignal( static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()), yystack_[2].value.as < std::string > ());
		 if ( signal != nullptr ) {
		   auto& attribute = signal->CreateAttribute( definition );
           attribute.Value(yystack_[1].value.as< std::string > ());
	     }
	     scanner.ResetTempList();
	  }
#line 863 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 61: // attribute_rel: TAG_BA_REL STRING_VAL TAG_BU_SG_REL ID_VAL TAG_SG INT_VAL ID_VAL attribute_value TAG_SEMICOLON
#line 310 "D:/projects/dbclib/src/dbcparser.y"
          {
		/* To be defined */
		scanner.ResetTempList();
	  }
#line 872 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 65: // attribute_definition_default: attribute_definition_object_or_relation STRING_VAL double_val TAG_SEMICOLON
#line 326 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition( yystack_[2].value.as < std::string > () );
		definition.Value( yystack_[1].value.as< double > () );
		scanner.ResetTempList();
	  }
#line 883 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 66: // attribute_definition_default: attribute_definition_object_or_relation STRING_VAL STRING_VAL TAG_SEMICOLON
#line 333 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition( yystack_[2].value.as < std::string > () );
		definition.Value( yystack_[1].value.as < std::string > () );
		scanner.ResetTempList();
	  }
#line 894 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 67: // attribute_definition_object_or_relation: TAG_BA_DEF_DEF
#line 341 "D:/projects/dbclib/src/dbcparser.y"
                      { yylhs.value.as< bool > () = false; }
#line 900 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 68: // attribute_definition_object_or_relation: TAG_BA_DEF_DEF_REL
#line 342 "D:/projects/dbclib/src/dbcparser.y"
                         { yylhs.value.as< bool > () = true; }
#line 906 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 69: // attribute_definition: attribute_object_type STRING_VAL TAG_INT INT_VAL INT_VAL TAG_SEMICOLON
#line 348 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as< AttributeType > () );
       	definition.ValueType( AttributeValueType::IntegerValue);
		definition.Min(static_cast<double>( yystack_[2].value.as < int64_t > () ));
		definition.Max(static_cast<double>( yystack_[1].value.as < int64_t > () ));
		scanner.ResetTempList();
	  }
#line 920 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 70: // attribute_definition: attribute_object_type STRING_VAL TAG_FLOAT double_val double_val TAG_SEMICOLON
#line 358 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as< AttributeType > () );
       	definition.ValueType( AttributeValueType::FloatValue);
		definition.Min( yystack_[2].value.as< double > () );
		definition.Max( yystack_[1].value.as< double > () );
		scanner.ResetTempList();
	  }
#line 934 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 71: // attribute_definition: attribute_object_type STRING_VAL TAG_STRING TAG_SEMICOLON
#line 368 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[2].value.as < std::string > () );
       	definition.Type( yystack_[3].value.as< AttributeType > () );
       	definition.ValueType( AttributeValueType::StringValue);
       	scanner.ResetTempList();
	  }
#line 946 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 72: // attribute_definition: attribute_object_type STRING_VAL TAG_ENUM comma_string_list TAG_SEMICOLON
#line 376 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[3].value.as < std::string > () );
       	definition.Type( yystack_[4].value.as< AttributeType > () );
       	definition.ValueType( AttributeValueType::EnumValue);
       	const auto& list = scanner.StringList();
        definition.EnumList(list);
		scanner.ResetTempList();
	  }
#line 960 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 73: // attribute_definition: attribute_object_type STRING_VAL TAG_HEX INT_VAL INT_VAL TAG_SEMICOLON
#line 386 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as< AttributeType > () );
       	definition.ValueType( AttributeValueType::HexValue);
		definition.Min(static_cast<double>( yystack_[2].value.as < int64_t > () ));
		definition.Max(static_cast<double>( yystack_[1].value.as < int64_t > () ));
		scanner.ResetTempList();
	  }
#line 974 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 74: // attribute_object_type: TAG_BA_DEF
#line 397 "D:/projects/dbclib/src/dbcparser.y"
                                   { yylhs.value.as< AttributeType > () = AttributeType::DbcNetwork; }
#line 980 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 75: // attribute_object_type: TAG_BA_DEF TAG_BU
#line 398 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as< AttributeType > () = AttributeType::DbcNode; }
#line 986 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 76: // attribute_object_type: TAG_BA_DEF TAG_BO
#line 399 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as< AttributeType > () = AttributeType::DbcMessage; }
#line 992 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 77: // attribute_object_type: TAG_BA_DEF TAG_SG
#line 400 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as< AttributeType > () = AttributeType::DbcSignal; }
#line 998 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 78: // attribute_object_type: TAG_BA_DEF TAG_EV
#line 401 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as< AttributeType > () = AttributeType::EnvironmentVariable; }
#line 1004 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 79: // attribute_object_type: TAG_BA_DEF_REL TAG_BU_SG_REL
#line 403 "D:/projects/dbclib/src/dbcparser.y"
                                   { yylhs.value.as< AttributeType > () = AttributeType::NodeSignalRelation; }
#line 1010 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 80: // attribute_object_type: TAG_BA_DEF_REL TAG_BU_BO_REL
#line 405 "D:/projects/dbclib/src/dbcparser.y"
                                   { yylhs.value.as< AttributeType > () = AttributeType::NodeMessageRelation; }
#line 1016 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 83: // val: TAG_VAL INT_VAL ID_VAL val_map TAG_SEMICOLON
#line 418 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
	    auto* signal = network.GetSignal(static_cast<uint64_t>( yystack_[3].value.as < int64_t > () ), yystack_[2].value.as < std::string > ());
	    if (signal != nullptr) {
	        const auto& list = scanner.EnumList();
	        signal->EnumList(list);
	    }
	    scanner.ResetTempList();
	}
#line 1030 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 84: // val: TAG_VAL ID_VAL val_map TAG_SEMICOLON
#line 429 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
	    auto& env_var = network.GetEnvVar( yystack_[2].value.as < std::string > () );
	    const auto& list = scanner.EnumList();
	    env_var.EnumList(list);
	    scanner.ResetTempList();
	}
#line 1042 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 87: // val_map_entry: INT_VAL STRING_VAL
#line 444 "D:/projects/dbclib/src/dbcparser.y"
        {
	    scanner.AddToEnumList(yystack_[1].value.as < int64_t > (), yystack_[0].value.as < std::string > () ); /* Temp storage on network */
	}
#line 1050 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 90: // sig_valtype: TAG_SIG_VALTYPE INT_VAL ID_VAL TAG_COLON INT_VAL TAG_SEMICOLON
#line 466 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
	    auto* signal = network.GetSignal(static_cast<uint64_t>(yystack_[4].value.as < int64_t > ()), yystack_[3].value.as < std::string > ());

	    if (signal != nullptr) {
	        switch (yystack_[1].value.as < int64_t > ()) {
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
	}
#line 1074 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 93: // comment: TAG_CM STRING_VAL TAG_SEMICOLON
#line 495 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  network.Comment( yystack_[1].value.as < std::string > () );
	  scanner.ResetTempList();
    }
#line 1084 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 94: // comment: TAG_CM TAG_EV ID_VAL STRING_VAL TAG_SEMICOLON
#line 501 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto& env_var = network.GetEnvVar(yystack_[2].value.as < std::string > ());
	  env_var.Comment(yystack_[1].value.as < std::string > ());
	  scanner.ResetTempList();
    }
#line 1095 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 95: // comment: TAG_CM TAG_BU ID_VAL STRING_VAL TAG_SEMICOLON
#line 508 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto* node = network.GetNode( yystack_[2].value.as < std::string > () );
	  if ( node != nullptr ) {
	    node->Comment( yystack_[1].value.as < std::string > () );
	  }
	  scanner.ResetTempList();
    }
#line 1108 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 96: // comment: TAG_CM TAG_BO INT_VAL STRING_VAL TAG_SEMICOLON
#line 517 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto* message = network.GetMessage( static_cast<uint64_t>(yystack_[2].value.as < int64_t > ()));
	  if ( message != nullptr ) {
	    message->Comment( yystack_[1].value.as < std::string > () );
	  }
	  scanner.ResetTempList();
    }
#line 1121 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 97: // comment: TAG_CM TAG_SG INT_VAL ID_VAL STRING_VAL TAG_SEMICOLON
#line 526 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto* signal = network.GetSignal( static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()), yystack_[2].value.as < std::string > ());
	  if ( signal != nullptr ) {
	    signal->Comment( yystack_[1].value.as < std::string > () );
	  }
	  scanner.ResetTempList();
    }
#line 1134 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 100: // message: TAG_BO INT_VAL ID_VAL TAG_COLON INT_VAL ID_VAL
#line 542 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto& message = network.CreateMessage(static_cast<uint64_t>(yystack_[4].value.as < int64_t > ()));
	  message.Name(yystack_[3].value.as < std::string > ());
	  message.NofBytes(static_cast<size_t>(yystack_[1].value.as < int64_t > ()));
	  message.Node(yystack_[0].value.as < std::string > ());
	  scanner.ResetTempList();
    }
#line 1147 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 103: // signal: TAG_SG ID_VAL mux_info TAG_COLON INT_VAL TAG_SEP INT_VAL TAG_AT little_endian signedness TAG_PAR_OPEN double_val TAG_COMMA double_val TAG_PAR_CLOSE TAG_BOX_OPEN double_val TAG_SEP double_val TAG_BOX_CLOSE STRING_VAL comma_identifier_list
#line 579 "D:/projects/dbclib/src/dbcparser.y"
        {
		auto& network = scanner.GetNetwork();
		auto* message = network.LastMessage();
		if (message != nullptr) {
		    auto& signal = message->CreateSignal(yystack_[20].value.as < std::string > ());
		    const std::string mux = yystack_[19].value.as< std::string > ();
		    if (!mux.empty() && mux[0] == 'M') {
		      signal.Mux(MuxType::Multiplexor);
		      signal.MuxValue(0);
		    } else if (!mux.empty() && mux[0] == 'm') {
		      signal.Mux(MuxType::Multiplexed);
		      signal.MuxValue( std::stoi(mux.substr(1)) );
		    } else {
		      signal.Mux(MuxType::NotMultiplexed);
		      signal.MuxValue(0);
		    }
		    signal.BitStart(static_cast<size_t>(yystack_[17].value.as < int64_t > ()));
		    signal.BitLength(static_cast<size_t>(yystack_[15].value.as < int64_t > ()));
		    signal.LittleEndian(yystack_[13].value.as< bool > ());
		    signal.DataType(yystack_[12].value.as< SignalDataType > ());
		    signal.Scale(yystack_[10].value.as< double > ());
		    signal.Offset(yystack_[8].value.as< double > ());
		    signal.Min(yystack_[5].value.as< double > ());
            signal.Max(yystack_[3].value.as< double > ());
            signal.Unit(yystack_[1].value.as < std::string > ());
            const auto& list = scanner.StringList();
            signal.Receivers(list);
		}
		scanner.ResetTempList();
	}
#line 1182 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 104: // mux_info: %empty
#line 614 "D:/projects/dbclib/src/dbcparser.y"
    {
	  yylhs.value.as< std::string > () = "";
    }
#line 1190 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 105: // mux_info: ID_VAL
#line 618 "D:/projects/dbclib/src/dbcparser.y"
        {
		yylhs.value.as< std::string > () = yystack_[0].value.as < std::string > ();
 	}
#line 1198 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 108: // space_identifier_list: ID_VAL space_identifier_list
#line 627 "D:/projects/dbclib/src/dbcparser.y"
         {
		scanner.AddToStringList( yystack_[1].value.as < std::string > () );
	 }
#line 1206 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 110: // comma_identifier_list: ID_VAL
#line 634 "D:/projects/dbclib/src/dbcparser.y"
    {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1214 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 111: // comma_identifier_list: ID_VAL TAG_COMMA comma_identifier_list
#line 638 "D:/projects/dbclib/src/dbcparser.y"
    {
		scanner.AddToStringList( yystack_[2].value.as < std::string > () );
    }
#line 1222 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 112: // comma_string_list: STRING_VAL
#line 644 "D:/projects/dbclib/src/dbcparser.y"
        {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
	}
#line 1230 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 113: // comma_string_list: STRING_VAL TAG_COMMA comma_string_list
#line 648 "D:/projects/dbclib/src/dbcparser.y"
        {
		scanner.AddToStringList( yystack_[2].value.as < std::string > () );
	}
#line 1238 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 114: // double_val: DOUBLE_VAL
#line 654 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as< double > () = yystack_[0].value.as < double > (); }
#line 1244 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 115: // double_val: TAG_NAN
#line 655 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as< double > () = std::numeric_limits<double>::quiet_NaN(); }
#line 1250 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 116: // double_val: INT_VAL
#line 656 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as< double > () = static_cast<double>(yystack_[0].value.as < int64_t > ()); }
#line 1256 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 117: // little_endian: INT_VAL
#line 659 "D:/projects/dbclib/src/dbcparser.y"
                       { yylhs.value.as< bool > () = yystack_[0].value.as < int64_t > () == 1; }
#line 1262 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 118: // signedness: TAG_PLUS
#line 662 "D:/projects/dbclib/src/dbcparser.y"
               { yylhs.value.as< SignalDataType > () = SignalDataType::UnsignedData; }
#line 1268 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 119: // signedness: TAG_MINUS
#line 663 "D:/projects/dbclib/src/dbcparser.y"
                { yylhs.value.as< SignalDataType > () = SignalDataType::SignedData; }
#line 1274 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 121: // space_node_list: ID_VAL space_node_list
#line 671 "D:/projects/dbclib/src/dbcparser.y"
{
	scanner.AddToStringList( yystack_[1].value.as < std::string > () );
}
#line 1282 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 122: // node_list: TAG_BU TAG_COLON space_node_list
#line 676 "D:/projects/dbclib/src/dbcparser.y"
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
    }
#line 1298 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 125: // valtable: TAG_VAL_TABLE ID_VAL val_map TAG_SEMICOLON
#line 696 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& list = scanner.EnumList();
		auto& network = scanner.GetNetwork();
		network.AddValueTable(yystack_[2].value.as < std::string > (), list );
		scanner.ResetTempList();
	}
#line 1309 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 129: // signal_group: TAG_SIG_GROUP INT_VAL ID_VAL INT_VAL TAG_COLON signal_name_list TAG_SEMICOLON
#line 713 "D:/projects/dbclib/src/dbcparser.y"
  {
    auto& network = scanner.GetNetwork();
    SignalGroup temp;
    temp.MessageId(static_cast<uint64_t>(yystack_[5].value.as < int64_t > ()));
    temp.Name(yystack_[4].value.as < std::string > ());
    temp.Repetition(static_cast<size_t>(yystack_[3].value.as < int64_t > ()));
    const auto& list = scanner.StringList();
    temp.Signals(list);
    network.AddSignalGroup(temp);
    scanner.ResetTempList();
  }
#line 1325 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 134: // extended_mux: TAG_SG_MUL_VAL INT_VAL ID_VAL ID_VAL value_range_list TAG_SEMICOLON
#line 741 "D:/projects/dbclib/src/dbcparser.y"
    {
        auto& network = scanner.GetNetwork();
        auto* signal = network.GetSignal(static_cast<uint64_t>(yystack_[4].value.as < int64_t > ()), yystack_[3].value.as < std::string > ());
        if (signal != nullptr) {
            auto& mux = signal->CreateExtendedMux();
            mux.multiplexor = yystack_[2].value.as < std::string > ();
            const auto& list = scanner.RangeList();
            mux.range_list = list;
        }
        scanner.ResetTempList();
    }
#line 1341 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 137: // value_range: INT_VAL INT_VAL
#line 760 "D:/projects/dbclib/src/dbcparser.y"
    {
        const auto low = static_cast<size_t>(yystack_[1].value.as < int64_t > ());
        const auto high = static_cast<size_t>(-yystack_[0].value.as < int64_t > ()); /* Solves the integer problem) */
        scanner.AddToRangeList(low, high);
    }
#line 1351 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 138: // message_transmitters: TAG_BO_TX_BU INT_VAL TAG_COLON comma_identifier_list TAG_SEMICOLON
#line 768 "D:/projects/dbclib/src/dbcparser.y"
        {
		auto& network = scanner.GetNetwork();
		auto* message = network.GetMessage(static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()));
		if (message != nullptr) {
		    const auto& list = scanner.StringList();
		    for (const auto& node : list) {
		        message->Node(node);
		    }
		}
		scanner.ResetTempList();
	}
#line 1367 "D:/projects/dbclib/src/dbcparser.cpp"
    break;


#line 1371 "D:/projects/dbclib/src/dbcparser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  DbcParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  DbcParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const short DbcParser::yypact_ninf_ = -194;

  const signed char DbcParser::yytable_ninf_ = -1;

  const short
  DbcParser::yypact_[] =
  {
      12,   -26,    42,    31,  -194,  -194,    43,    41,   149,    56,
      44,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
     149,     2,    59,    27,  -194,    60,     9,    10,    52,    27,
      13,     9,  -194,    14,    15,    29,    50,  -194,    61,  -194,
      18,    72,    14,    21,    20,    29,    62,    23,    52,    50,
      22,  -194,  -194,  -194,    79,    80,  -194,    28,    54,    62,
      30,  -194,  -194,  -194,    32,    33,    84,    35,    66,    54,
    -194,  -194,    90,    38,    82,    92,    39,    95,    -5,   -12,
      66,  -194,    45,  -194,    33,  -194,    91,    46,    47,    51,
      53,    57,    97,    26,  -194,   -40,  -194,    75,   -12,    55,
     -12,    58,  -194,   103,  -194,   -30,    98,    63,    64,    67,
      65,  -194,  -194,  -194,  -194,  -194,  -194,  -194,    68,    71,
      75,  -194,   -24,  -194,   -14,    69,  -194,  -194,  -194,   104,
    -194,   106,   112,    73,   113,    -9,    76,    93,    71,  -194,
     115,   120,    70,   -30,    77,    74,   122,   123,   -30,  -194,
    -194,   131,  -194,    78,    81,    85,  -194,  -194,  -194,   134,
      94,   -38,   114,    93,  -194,  -194,  -194,    86,   -30,   129,
     141,    88,  -194,    89,   138,  -194,    -4,    -4,    96,  -194,
      99,    14,   100,   101,   126,   114,  -194,   145,   146,    77,
    -194,   150,  -194,     8,   105,   153,   154,    -4,   143,   159,
      14,   109,     6,   127,   126,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,   156,   -30,  -194,  -194,   164,   140,  -194,   195,
     142,   144,   147,   148,   163,   127,  -194,   -30,   151,  -194,
     152,  -194,   201,   155,   157,   158,   160,   163,   162,  -194,
     194,   161,    -4,  -194,   207,   208,   214,   165,  -194,   166,
    -194,   162,   -30,    33,   215,  -194,  -194,   167,   168,   171,
    -194,   210,   216,  -194,   219,   225,   173,   221,  -194,  -194,
     175,   174,   -30,   175,   229,  -194,   176,   231,   174,   232,
    -194,  -194,  -194,  -194,  -194,   -30,   226,   181,    33,  -194
  };

  const unsigned char
  DbcParser::yydefact_[] =
  {
       0,     0,     0,     4,     3,     1,     0,   126,     5,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,     6,
       7,   127,     0,   123,     8,     0,   120,     0,    98,   123,
       0,   120,   122,    85,     0,   139,   101,   124,     0,   121,
       0,     0,    85,     0,     0,   139,    37,     0,    98,   101,
       0,    87,   125,    86,     0,     0,   140,     0,    40,    37,
     104,    99,   102,   128,     0,   109,     0,     0,    91,    40,
      38,   105,     0,     0,   110,     0,     0,     0,     0,    62,
      91,    41,     0,   100,   109,   138,     0,     0,     0,     0,
       0,     0,     0,    74,    67,     0,    68,    53,    62,     0,
      62,     0,    92,     0,   111,     0,     0,     0,     0,     0,
       0,    93,    76,    75,    77,    78,    79,    80,     0,    59,
      53,    63,     0,    64,     0,     0,   115,   116,   114,     0,
      42,     0,     0,     0,     0,     0,     0,    81,    59,    54,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
      95,     0,    94,     0,     0,     0,    51,    50,    52,     0,
       0,     0,    43,    81,    60,    66,    65,     0,     0,   112,
       0,     0,    71,     0,     0,    97,     0,     0,     0,    55,
       0,    85,     0,     0,    46,    43,    82,     0,     0,     0,
      72,     0,   117,     0,     0,     0,     0,     0,     0,     0,
      85,     0,     0,    88,    46,    44,    69,    70,   113,    73,
     118,   119,     0,     0,    57,    56,     0,     0,    84,     0,
       0,     0,     0,     0,   130,    88,    47,     0,     0,    58,
       0,    83,     0,     0,     0,     0,     0,   130,   132,    89,
       0,     0,     0,    45,     0,     0,     0,     0,   131,     0,
       2,   132,     0,   109,     0,    49,    48,     0,     0,     0,
     133,     0,     0,    61,     0,     0,     0,     0,    39,    90,
     107,     0,     0,   107,     0,   106,     0,     0,   135,     0,
     108,   129,   137,   134,   136,     0,     0,     0,   109,   103
  };

  const short
  DbcParser::yypgoto_[] =
  {
    -194,  -194,  -194,  -194,   199,  -194,   169,  -194,   170,  -194,
      36,  -194,    16,  -194,  -193,   102,  -194,    87,  -194,   -62,
    -194,  -194,  -194,  -194,    83,  -194,   -60,  -194,    -2,  -194,
     172,  -194,   178,  -194,   180,  -194,  -194,  -194,   -49,  -104,
      48,  -141,  -194,  -194,   196,  -194,   202,  -194,  -194,  -194,
      -7,   -19,  -194,   -45,  -194,  -194,   189
  };

  const short
  DbcParser::yydefgoto_[] =
  {
       0,     2,     3,     7,    39,    40,    78,    79,    88,    89,
     204,   205,   223,   224,   179,   139,   140,   157,   158,   117,
     118,   119,   120,   121,   182,   183,    61,    62,   244,   245,
      99,   100,    55,    56,    68,    69,    92,   294,   295,    95,
     190,   149,   213,   232,    52,    43,    48,    49,    10,   257,
     258,   270,   271,   297,   298,    65,    66
  };

  const short
  DbcParser::yytable_[] =
  {
     124,   161,    73,   215,   216,   136,   173,   137,   174,   175,
     108,   113,   109,   110,   111,   230,   231,   114,   201,   146,
     202,   241,   188,   242,   236,   146,     1,   194,   147,   148,
     115,     4,   116,   160,   147,   148,   162,   163,   164,   165,
     166,   132,     5,   133,   134,   135,     8,   208,   176,   177,
     178,     6,   112,   176,   177,   178,   141,     9,   143,    41,
      45,    42,    46,    50,    47,    51,    53,    54,    67,   274,
      64,    58,    60,    63,    70,    71,    72,    74,    75,    80,
      83,    77,    84,    85,    86,    87,    91,    96,    98,    94,
      93,    97,   248,   102,   103,   104,   105,   106,   107,   138,
     125,   131,   150,   123,   126,   127,   260,   128,   145,   168,
     169,   129,   142,   130,   156,   144,   170,   172,   181,   185,
     151,   152,   154,   153,   186,   155,   192,   167,   187,   193,
     171,   281,   191,   180,   189,   195,   196,   197,   199,   200,
     203,   219,   209,   198,   207,   210,   211,   212,   214,   226,
     227,   299,   217,   222,   229,   218,   220,   234,   235,   221,
     239,   237,   233,   238,   306,   240,   243,   247,   249,   282,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   250,   251,
     252,   256,   253,   254,   309,   263,   255,   272,   262,   261,
     269,   275,   276,   264,   266,   265,   273,   277,   267,   283,
     288,   278,   287,   289,   279,   284,   285,   286,   290,   291,
     292,   293,   296,   301,   302,   303,   307,   305,   308,    44,
     246,   225,   159,   259,   300,   184,    81,    59,    90,    82,
     268,    57,   280,   304,    76,     0,     0,   228,     0,   101,
       0,     0,     0,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   122
  };

  const short
  DbcParser::yycheck_[] =
  {
     104,   142,    62,   196,   197,    45,    15,    47,    17,    18,
      15,    23,    17,    18,    19,     7,     8,    29,    56,    49,
      58,    15,   163,    17,   217,    49,    14,   168,    58,    59,
      42,    57,    44,    57,    58,    59,    50,    51,    52,    53,
      54,    15,     0,    17,    18,    19,     3,   188,    57,    58,
      59,    20,    57,    57,    58,    59,   118,    16,   120,     3,
      58,    17,     3,     3,    37,    56,    56,    15,    18,   262,
      41,    58,    58,    58,    13,    57,     4,    56,    58,    56,
      58,    19,     3,     3,    56,    31,    56,     3,    22,    56,
      58,    56,   233,     3,    56,    13,     4,    58,     3,    24,
       9,     4,     4,    58,    58,    58,   247,    56,     5,     5,
       4,    58,    57,    56,    43,    57,     4,     4,    25,     4,
      57,    57,    57,    56,     4,    57,     4,    58,    58,     6,
      57,   272,    58,    57,    57,     4,    58,    56,     4,    45,
      26,   201,    13,    58,    58,     4,    58,    58,    10,     4,
       4,   292,    56,    27,     4,    56,    56,     4,     4,    58,
     220,    18,    57,     4,   305,    56,    39,    11,     4,   273,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    58,     4,
      58,    38,    58,    56,   308,     4,    58,    13,    56,    58,
      48,     4,     4,    58,    56,    58,    55,     3,    58,     4,
       4,    56,    12,     4,    58,    58,    58,    56,     3,    56,
       9,    56,    58,     4,    58,     4,    10,     5,    57,    40,
     224,   205,   140,   245,   293,   158,    68,    51,    79,    69,
     257,    49,   271,   298,    65,    -1,    -1,   209,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,   183,    -1,    -1,    -1,
      -1,    -1,   100
  };

  const signed char
  DbcParser::yystos_[] =
  {
       0,    14,    63,    64,    57,     0,    20,    65,     3,    16,
     110,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    66,
      67,     3,    17,   107,    66,    58,     3,    37,   108,   109,
       3,    56,   106,    56,    15,    94,    95,   108,    58,   106,
      58,    88,    89,    58,    41,   117,   118,    18,    96,    97,
      13,    57,     4,    88,    56,    58,   118,    19,    68,    69,
      56,    94,    96,    58,     3,     3,    56,    31,    70,    71,
      68,    56,    98,    58,    56,   101,     3,    56,    22,    92,
      93,    70,     3,    56,    13,     4,    58,     3,    15,    17,
      18,    19,    57,    23,    29,    42,    44,    81,    82,    83,
      84,    85,    92,    58,   101,     9,    58,    58,    56,    58,
      56,     4,    15,    17,    18,    19,    45,    47,    24,    77,
      78,    81,    57,    81,    57,     5,    49,    58,    59,   103,
       4,    57,    57,    56,    57,    57,    43,    79,    80,    77,
      57,   103,    50,    51,    52,    53,    54,    58,     5,     4,
       4,    57,     4,    15,    17,    18,    57,    58,    59,    76,
      57,    25,    86,    87,    79,     4,     4,    58,   103,    57,
     102,    58,     4,     6,   103,     4,    58,    56,    58,     4,
      45,    56,    58,    26,    72,    73,    86,    58,   103,    13,
       4,    58,    58,   104,    10,    76,    76,    56,    56,    88,
      56,    58,    27,    74,    75,    72,     4,     4,   102,     4,
       7,     8,   105,    57,     4,     4,    76,    18,     4,    88,
      56,    15,    17,    39,    90,    91,    74,    11,   103,     4,
      58,     4,    58,    58,    56,    58,    38,   111,   112,    90,
     103,    58,    56,     4,    58,    58,    56,    58,   112,    48,
     113,   114,    13,    55,    76,     4,     4,     3,    56,    58,
     113,   103,   101,     4,    58,    58,    56,    12,     4,     4,
       3,    56,     9,    56,    99,   100,    58,   115,   116,   103,
     100,     4,    58,     4,   115,     5,   103,    10,    57,   101
  };

  const signed char
  DbcParser::yyr1_[] =
  {
       0,    62,    63,    64,    65,    65,    65,    66,    66,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    69,
      70,    70,    71,    72,    72,    73,    74,    74,    75,    75,
      76,    76,    76,    77,    77,    78,    78,    78,    78,    79,
      79,    80,    81,    81,    81,    82,    82,    83,    83,    84,
      84,    84,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    90,    90,
      91,    92,    92,    93,    93,    93,    93,    93,    94,    94,
      95,    96,    96,    97,    98,    98,    99,   100,   100,   101,
     101,   101,   102,   102,   103,   103,   103,   104,   105,   105,
     106,   106,   107,   108,   108,   109,   110,   110,   110,   111,
     112,   112,   113,   113,   114,   115,   115,   116,   117,   118,
     118
  };

  const signed char
  DbcParser::yyr2_[] =
  {
       0,     2,    19,     2,     0,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     2,    15,
       0,     2,     5,     0,     2,     5,     0,     2,     5,     5,
       1,     1,     1,     0,     2,     4,     6,     6,     7,     0,
       2,     9,     0,     2,     2,     4,     4,     1,     1,     6,
       6,     4,     5,     6,     1,     2,     2,     2,     2,     2,
       2,     0,     2,     5,     4,     0,     2,     2,     0,     2,
       6,     0,     2,     3,     5,     5,     5,     6,     0,     3,
       6,     0,     2,    22,     0,     1,     1,     0,     2,     0,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     2,     3,     0,     2,     4,     0,     2,     7,     7,
       0,     2,     0,     2,     6,     1,     2,     2,     5,     0,
       2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const DbcParser::yytname_[] =
  {
  "EOL", "error", "\"invalid token\"", "TAG_COLON", "TAG_SEMICOLON",
  "TAG_SEP", "TAG_AT", "TAG_PLUS", "TAG_MINUS", "TAG_BOX_OPEN",
  "TAG_BOX_CLOSE", "TAG_PAR_OPEN", "TAG_PAR_CLOSE", "TAG_COMMA",
  "TAG_VERSION", "TAG_BO", "TAG_BS", "TAG_BU", "TAG_SG", "TAG_EV",
  "TAG_NS", "TAG_NS_DESC", "TAG_CM", "TAG_BA_DEF", "TAG_BA", "TAG_VAL",
  "TAG_CAT_DEF", "TAG_CAT", "TAG_FILTER", "TAG_BA_DEF_DEF", "TAG_EV_DATA",
  "TAG_ENVVAR_DATA", "TAG_SGTYPE", "TAG_SGTYPE_VAL", "TAG_BA_DEF_SGTYPE",
  "TAG_BA_SGTYPE", "TAG_SIG_TYPE_REF", "TAG_VAL_TABLE", "TAG_SIG_GROUP",
  "TAG_SIG_VALTYPE", "TAG_SIGTYPE_VALTYPE", "TAG_BO_TX_BU",
  "TAG_BA_DEF_REL", "TAG_BA_REL", "TAG_BA_DEF_DEF_REL", "TAG_BU_SG_REL",
  "TAG_BU_EV_REL", "TAG_BU_BO_REL", "TAG_SG_MUL_VAL", "TAG_NAN", "TAG_INT",
  "TAG_FLOAT", "TAG_ENUM", "TAG_HEX", "TAG_STRING",
  "TAG_DUMMY_NODE_VECTOR", "ID_VAL", "STRING_VAL", "INT_VAL", "DOUBLE_VAL",
  "ENUM_VAL", "HEX_VAL", "$accept", "dbc_file", "version",
  "symbol_section", "symbol_list", "symbol", "envvar_list", "envvar",
  "envvar_data_list", "envvar_data", "category_definition_list",
  "category_definition", "category_list", "category", "attribute_value",
  "attribute_list", "attribute", "attribute_rel_list", "attribute_rel",
  "attribute_def_list", "attribute_definition_default",
  "attribute_definition_object_or_relation", "attribute_definition",
  "attribute_object_type", "val_list", "val", "val_map", "val_map_entry",
  "sig_valtype_list", "sig_valtype", "comment_list", "comment",
  "message_list", "message", "signal_list", "signal", "mux_info",
  "signal_name_list", "space_identifier_list", "comma_identifier_list",
  "comma_string_list", "double_val", "little_endian", "signedness",
  "space_node_list", "node_list", "valtable_list", "valtable",
  "message_section", "signal_group", "signal_group_list",
  "extended_mux_list", "extended_mux", "value_range_list", "value_range",
  "message_transmitters", "message_transmitter_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  DbcParser::yyrline_[] =
  {
       0,    88,    88,   109,   117,   118,   119,   122,   123,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   157,   158,   163,
     194,   195,   198,   207,   208,   211,   214,   215,   218,   219,
     222,   223,   224,   228,   229,   233,   244,   260,   276,   295,
     296,   301,   317,   318,   319,   325,   332,   341,   342,   347,
     357,   367,   375,   385,   397,   398,   399,   400,   401,   403,
     405,   411,   412,   417,   428,   438,   439,   443,   452,   453,
     465,   489,   490,   494,   500,   507,   516,   525,   536,   537,
     541,   552,   553,   557,   613,   617,   622,   625,   626,   632,
     633,   637,   643,   647,   654,   655,   656,   659,   662,   663,
     669,   670,   675,   689,   690,   695,   705,   706,   707,   712,
     727,   728,   731,   732,   735,   754,   755,   758,   766,   781,
     782
  };

  void
  DbcParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  DbcParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  DbcParser::symbol_kind_type
  DbcParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
    };
    // Last valid token kind.
    const int code_max = 316;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "D:/projects/dbclib/src/dbcparser.y"
} // dbc
#line 1943 "D:/projects/dbclib/src/dbcparser.cpp"

#line 785 "D:/projects/dbclib/src/dbcparser.y"



void dbc::DbcParser::error(const std::string& err) {
    const auto line = scanner.lineno();
    const auto column = scanner.YYLeng();
    const std::string near = scanner.YYText();

    std::cout << "Error: " << err
              << ", Line: " << line
              << ", Column: " << column
              << ", Near: " << near
               << std::endl;
}
