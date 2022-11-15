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


// Take the name prefix into account.
#define yylex   ddlex



#include "dbcparser.hpp"


// Unqualified %code blocks.
#line 20 "D:/projects/dbclib/src/dbcparser.y"

    #include <sstream>
    #include "dbcscanner.h"

    #undef yylex
    #define yylex scanner.ddlex

#line 56 "D:/projects/dbclib/src/dbcparser.cpp"


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
#if DDDEBUG

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

#else // !DDDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !DDDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 6 "D:/projects/dbclib/src/dbcparser.y"
namespace dbc {
#line 130 "D:/projects/dbclib/src/dbcparser.cpp"

  /// Build a parser object.
  DbcParser::DbcParser (dbc::DbcScanner &scanner_yyarg)
#if DDDEBUG
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
      case symbol_kind::S_attribute_object_type: // attribute_object_type
        value.copy< AttributeType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_signedness: // signedness
        value.copy< SignalDataType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_attribute_definition_object_or_relation: // attribute_definition_object_or_relation
      case symbol_kind::S_little_endian: // little_endian
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
      case symbol_kind::S_double_val: // double_val
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
      case symbol_kind::S_attribute_value: // attribute_value
      case symbol_kind::S_mux_info: // mux_info
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
      case symbol_kind::S_attribute_object_type: // attribute_object_type
        value.move< AttributeType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_signedness: // signedness
        value.move< SignalDataType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_attribute_definition_object_or_relation: // attribute_definition_object_or_relation
      case symbol_kind::S_little_endian: // little_endian
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
      case symbol_kind::S_double_val: // double_val
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
      case symbol_kind::S_attribute_value: // attribute_value
      case symbol_kind::S_mux_info: // mux_info
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
      case symbol_kind::S_attribute_object_type: // attribute_object_type
        value.YY_MOVE_OR_COPY< AttributeType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_signedness: // signedness
        value.YY_MOVE_OR_COPY< SignalDataType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_attribute_definition_object_or_relation: // attribute_definition_object_or_relation
      case symbol_kind::S_little_endian: // little_endian
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
      case symbol_kind::S_double_val: // double_val
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
      case symbol_kind::S_attribute_value: // attribute_value
      case symbol_kind::S_mux_info: // mux_info
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
      case symbol_kind::S_attribute_object_type: // attribute_object_type
        value.move< AttributeType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_signedness: // signedness
        value.move< SignalDataType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_attribute_definition_object_or_relation: // attribute_definition_object_or_relation
      case symbol_kind::S_little_endian: // little_endian
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
      case symbol_kind::S_double_val: // double_val
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
      case symbol_kind::S_attribute_value: // attribute_value
      case symbol_kind::S_mux_info: // mux_info
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
      case symbol_kind::S_attribute_object_type: // attribute_object_type
        value.copy< AttributeType > (that.value);
        break;

      case symbol_kind::S_signedness: // signedness
        value.copy< SignalDataType > (that.value);
        break;

      case symbol_kind::S_attribute_definition_object_or_relation: // attribute_definition_object_or_relation
      case symbol_kind::S_little_endian: // little_endian
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
      case symbol_kind::S_double_val: // double_val
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
      case symbol_kind::S_attribute_value: // attribute_value
      case symbol_kind::S_mux_info: // mux_info
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
      case symbol_kind::S_attribute_object_type: // attribute_object_type
        value.move< AttributeType > (that.value);
        break;

      case symbol_kind::S_signedness: // signedness
        value.move< SignalDataType > (that.value);
        break;

      case symbol_kind::S_attribute_definition_object_or_relation: // attribute_definition_object_or_relation
      case symbol_kind::S_little_endian: // little_endian
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
      case symbol_kind::S_double_val: // double_val
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
      case symbol_kind::S_attribute_value: // attribute_value
      case symbol_kind::S_mux_info: // mux_info
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

#if DDDEBUG
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

#if DDDEBUG
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
#endif // DDDEBUG

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
      case symbol_kind::S_attribute_object_type: // attribute_object_type
        yylhs.value.emplace< AttributeType > ();
        break;

      case symbol_kind::S_signedness: // signedness
        yylhs.value.emplace< SignalDataType > ();
        break;

      case symbol_kind::S_attribute_definition_object_or_relation: // attribute_definition_object_or_relation
      case symbol_kind::S_little_endian: // little_endian
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
      case symbol_kind::S_double_val: // double_val
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
      case symbol_kind::S_attribute_value: // attribute_value
      case symbol_kind::S_mux_info: // mux_info
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
#line 125 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
		network.Version(yystack_[0].value.as < std::string > ());
		scanner.ResetTempList();
	}
#line 875 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 39: // envvar: TAG_EV ID_VAL TAG_COLON INT_VAL TAG_BOX_OPEN double_val TAG_SEP double_val TAG_BOX_CLOSE STRING_VAL double_val INT_VAL TAG_DUMMY_NODE_VECTOR comma_identifier_list TAG_SEMICOLON
#line 193 "D:/projects/dbclib/src/dbcparser.y"
    {
        auto& network = scanner.GetNetwork();
        auto& env_var = network.GetEnvVar(yystack_[13].value.as < std::string > ());
        env_var.Type(static_cast<EnvType>(yystack_[11].value.as < int64_t > ()));
        env_var.Min( yystack_[9].value.as < double > () );
        env_var.Max( yystack_[7].value.as < double > () );
        env_var.Unit( yystack_[5].value.as < std::string > () );
        env_var.InitValue(yystack_[4].value.as < double > ());
        env_var.Ident(static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()));
        env_var.Access(static_cast<AccessType>(yystack_[2].value.as < int > ()));
        const auto& list = scanner.StringList();
        env_var.NodeList(list);
        scanner.ResetTempList();
    }
#line 894 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 42: // envvar_data: TAG_ENVVAR_DATA ID_VAL TAG_COLON INT_VAL TAG_SEMICOLON
#line 216 "D:/projects/dbclib/src/dbcparser.y"
          {
		/* To be defined what to do here */
		scanner.ResetTempList();
	  }
#line 903 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 50: // attribute_value: INT_VAL
#line 238 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < std::string > () = std::to_string(yystack_[0].value.as < int64_t > ()); }
#line 909 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 51: // attribute_value: STRING_VAL
#line 239 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 915 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 52: // attribute_value: DOUBLE_VAL
#line 240 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < std::string > () = std::to_string(yystack_[0].value.as < double > ()); }
#line 921 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 55: // attribute: TAG_BA STRING_VAL attribute_value TAG_SEMICOLON
#line 251 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition(yystack_[2].value.as < std::string > ());
		auto& attribute = network.CreateAttribute( definition );
		attribute.Value(yystack_[1].value.as < std::string > ());
		scanner.ResetTempList();
	  }
#line 933 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 56: // attribute: TAG_BA STRING_VAL TAG_BU ID_VAL attribute_value TAG_SEMICOLON
#line 264 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition(yystack_[4].value.as < std::string > ());
		auto* node = network.GetNode( yystack_[2].value.as < std::string > () );
		if ( node != nullptr) {
			auto& attribute = node->CreateAttribute( definition );
            attribute.Value(yystack_[1].value.as < std::string > ());
		}
		scanner.ResetTempList();
	  }
#line 948 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 57: // attribute: TAG_BA STRING_VAL TAG_BO INT_VAL attribute_value TAG_SEMICOLON
#line 280 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition(yystack_[4].value.as < std::string > ());
		auto* message = network.GetMessage( static_cast<uint64_t>(yystack_[2].value.as < int64_t > ()));
		if ( message != nullptr ) {
			auto& attribute = message->CreateAttribute( definition );
            attribute.Value(yystack_[1].value.as < std::string > ());
		}
		scanner.ResetTempList();
	  }
#line 963 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 58: // attribute: TAG_BA STRING_VAL TAG_SG INT_VAL ID_VAL attribute_value TAG_SEMICOLON
#line 297 "D:/projects/dbclib/src/dbcparser.y"
          {
		 auto& network = scanner.GetNetwork();
		 auto& definition = network.GetDefinition(yystack_[5].value.as < std::string > ());
		 auto* signal = network.GetSignal( static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()), yystack_[2].value.as < std::string > ());
		 if ( signal != nullptr ) {
		   auto& attribute = signal->CreateAttribute( definition );
           attribute.Value(yystack_[1].value.as < std::string > ());
	     }
	     scanner.ResetTempList();
	  }
#line 978 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 61: // attribute_rel: TAG_BA_REL STRING_VAL TAG_BU_SG_REL ID_VAL TAG_SG INT_VAL ID_VAL attribute_value TAG_SEMICOLON
#line 323 "D:/projects/dbclib/src/dbcparser.y"
          {
		/* To be defined */
		scanner.ResetTempList();
	  }
#line 987 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 65: // attribute_definition_default: attribute_definition_object_or_relation STRING_VAL double_val TAG_SEMICOLON
#line 338 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition( yystack_[2].value.as < std::string > () );
		definition.Value( yystack_[1].value.as < double > () );
		scanner.ResetTempList();
	  }
#line 998 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 66: // attribute_definition_default: attribute_definition_object_or_relation STRING_VAL STRING_VAL TAG_SEMICOLON
#line 345 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.GetDefinition( yystack_[2].value.as < std::string > () );
		definition.Value( yystack_[1].value.as < std::string > () );
		scanner.ResetTempList();
	  }
#line 1009 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 67: // attribute_definition_object_or_relation: TAG_BA_DEF_DEF
#line 353 "D:/projects/dbclib/src/dbcparser.y"
                      { yylhs.value.as < bool > () = false; }
#line 1015 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 68: // attribute_definition_object_or_relation: TAG_BA_DEF_DEF_REL
#line 354 "D:/projects/dbclib/src/dbcparser.y"
                         { yylhs.value.as < bool > () = true; }
#line 1021 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 69: // attribute_definition: attribute_object_type STRING_VAL TAG_INT INT_VAL INT_VAL TAG_SEMICOLON
#line 360 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::IntegerValue);
		definition.Min(static_cast<double>( yystack_[2].value.as < int64_t > () ));
		definition.Max(static_cast<double>( yystack_[1].value.as < int64_t > () ));
		scanner.ResetTempList();
	  }
#line 1035 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 70: // attribute_definition: attribute_object_type STRING_VAL TAG_FLOAT double_val double_val TAG_SEMICOLON
#line 370 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::FloatValue);
		definition.Min( yystack_[2].value.as < double > () );
		definition.Max( yystack_[1].value.as < double > () );
		scanner.ResetTempList();
	  }
#line 1049 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 71: // attribute_definition: attribute_object_type STRING_VAL TAG_STRING TAG_SEMICOLON
#line 380 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[2].value.as < std::string > () );
       	definition.Type( yystack_[3].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::StringValue);
       	scanner.ResetTempList();
	  }
#line 1061 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 72: // attribute_definition: attribute_object_type STRING_VAL TAG_ENUM comma_string_list TAG_SEMICOLON
#line 388 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[3].value.as < std::string > () );
       	definition.Type( yystack_[4].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::EnumValue);
       	const auto& list = scanner.StringList();
        definition.EnumList(list);
		scanner.ResetTempList();
	  }
#line 1075 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 73: // attribute_definition: attribute_object_type STRING_VAL TAG_HEX INT_VAL INT_VAL TAG_SEMICOLON
#line 398 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.GetDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::HexValue);
		definition.Min(static_cast<double>( yystack_[2].value.as < int64_t > () ));
		definition.Max(static_cast<double>( yystack_[1].value.as < int64_t > () ));
		scanner.ResetTempList();
	  }
#line 1089 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 74: // attribute_object_type: TAG_BA_DEF
#line 409 "D:/projects/dbclib/src/dbcparser.y"
                                   { yylhs.value.as < AttributeType > () = AttributeType::DbcNetwork; }
#line 1095 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 75: // attribute_object_type: TAG_BA_DEF TAG_BU
#line 410 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as < AttributeType > () = AttributeType::DbcNode; }
#line 1101 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 76: // attribute_object_type: TAG_BA_DEF TAG_BO
#line 411 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as < AttributeType > () = AttributeType::DbcMessage; }
#line 1107 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 77: // attribute_object_type: TAG_BA_DEF TAG_SG
#line 412 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as < AttributeType > () = AttributeType::DbcSignal; }
#line 1113 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 78: // attribute_object_type: TAG_BA_DEF TAG_EV
#line 413 "D:/projects/dbclib/src/dbcparser.y"
                           { yylhs.value.as < AttributeType > () = AttributeType::EnvironmentVariable; }
#line 1119 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 79: // attribute_object_type: TAG_BA_DEF_REL TAG_BU_SG_REL
#line 415 "D:/projects/dbclib/src/dbcparser.y"
                                   { yylhs.value.as < AttributeType > () = AttributeType::NodeSignalRelation; }
#line 1125 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 80: // attribute_object_type: TAG_BA_DEF_REL TAG_BU_BO_REL
#line 417 "D:/projects/dbclib/src/dbcparser.y"
                                   { yylhs.value.as < AttributeType > () = AttributeType::NodeMessageRelation; }
#line 1131 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 83: // val: TAG_VAL INT_VAL ID_VAL val_map TAG_SEMICOLON
#line 430 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
	    auto* signal = network.GetSignal(static_cast<uint64_t>( yystack_[3].value.as < int64_t > () ), yystack_[2].value.as < std::string > ());
	    if (signal != nullptr) {
	        const auto& list = scanner.EnumList();
	        signal->EnumList(list);
	    }
	    scanner.ResetTempList();
	}
#line 1145 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 84: // val: TAG_VAL ID_VAL val_map TAG_SEMICOLON
#line 441 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
	    auto& env_var = network.GetEnvVar( yystack_[2].value.as < std::string > () );
	    const auto& list = scanner.EnumList();
	    env_var.EnumList(list);
	    scanner.ResetTempList();
	}
#line 1157 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 87: // val_map_entry: INT_VAL STRING_VAL
#line 456 "D:/projects/dbclib/src/dbcparser.y"
        {
	    scanner.AddToEnumList(yystack_[1].value.as < int64_t > (), yystack_[0].value.as < std::string > () ); /* Temp storage on network */
	}
#line 1165 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 90: // sig_valtype: TAG_SIG_VALTYPE INT_VAL ID_VAL TAG_COLON INT_VAL TAG_SEMICOLON
#line 477 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1189 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 93: // comment: TAG_CM STRING_VAL TAG_SEMICOLON
#line 505 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  network.Comment( yystack_[1].value.as < std::string > () );
	  scanner.ResetTempList();
    }
#line 1199 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 94: // comment: TAG_CM TAG_EV ID_VAL STRING_VAL TAG_SEMICOLON
#line 511 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto& env_var = network.GetEnvVar(yystack_[2].value.as < std::string > ());
	  env_var.Comment(yystack_[1].value.as < std::string > ());
	  scanner.ResetTempList();
    }
#line 1210 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 95: // comment: TAG_CM TAG_BU ID_VAL STRING_VAL TAG_SEMICOLON
#line 518 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto* node = network.GetNode( yystack_[2].value.as < std::string > () );
	  if ( node != nullptr ) {
	    node->Comment( yystack_[1].value.as < std::string > () );
	  }
	  scanner.ResetTempList();
    }
#line 1223 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 96: // comment: TAG_CM TAG_BO INT_VAL STRING_VAL TAG_SEMICOLON
#line 527 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto* message = network.GetMessage( static_cast<uint64_t>(yystack_[2].value.as < int64_t > ()));
	  if ( message != nullptr ) {
	    message->Comment( yystack_[1].value.as < std::string > () );
	  }
	  scanner.ResetTempList();
    }
#line 1236 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 97: // comment: TAG_CM TAG_SG INT_VAL ID_VAL STRING_VAL TAG_SEMICOLON
#line 536 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto* signal = network.GetSignal( static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()), yystack_[2].value.as < std::string > ());
	  if ( signal != nullptr ) {
	    signal->Comment( yystack_[1].value.as < std::string > () );
	  }
	  scanner.ResetTempList();
    }
#line 1249 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 100: // message: TAG_BO INT_VAL ID_VAL TAG_COLON INT_VAL ID_VAL
#line 552 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto& message = network.CreateMessage(static_cast<uint64_t>(yystack_[4].value.as < int64_t > ()));
	  message.Name(yystack_[3].value.as < std::string > ());
	  message.NofBytes(static_cast<size_t>(yystack_[1].value.as < int64_t > ()));
	  message.Node(yystack_[0].value.as < std::string > ());
	  scanner.ResetTempList();
    }
#line 1262 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 103: // signal: TAG_SG ID_VAL mux_info TAG_COLON INT_VAL TAG_SEP INT_VAL TAG_AT little_endian signedness TAG_PAR_OPEN double_val TAG_COMMA double_val TAG_PAR_CLOSE TAG_BOX_OPEN double_val TAG_SEP double_val TAG_BOX_CLOSE STRING_VAL comma_identifier_list
#line 589 "D:/projects/dbclib/src/dbcparser.y"
        {
		auto& network = scanner.GetNetwork();
		auto* message = network.LastMessage();
		if (message != nullptr) {
		    auto& signal = message->CreateSignal(yystack_[20].value.as < std::string > ());
		    signal.MessageId(message->Ident()); // Used to find its message later on
		    std::string mux = yystack_[19].value.as < std::string > ();
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
		    signal.BitStart(static_cast<size_t>(yystack_[17].value.as < int64_t > ()));
		    signal.BitLength(static_cast<size_t>(yystack_[15].value.as < int64_t > ()));
		    signal.LittleEndian(yystack_[13].value.as < bool > ());
		    signal.DataType(yystack_[12].value.as < SignalDataType > ());
		    signal.Scale(yystack_[10].value.as < double > ());
		    signal.Offset(yystack_[8].value.as < double > ());
		    signal.Min(yystack_[5].value.as < double > ());
            signal.Max(yystack_[3].value.as < double > ());
            signal.Unit(yystack_[1].value.as < std::string > ());
            const auto& list = scanner.StringList();
            signal.Receivers(list);
		}
		scanner.ResetTempList();
	}
#line 1303 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 104: // mux_info: %empty
#line 630 "D:/projects/dbclib/src/dbcparser.y"
    {
	  yylhs.value.as < std::string > () = "";
    }
#line 1311 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 105: // mux_info: ID_VAL
#line 634 "D:/projects/dbclib/src/dbcparser.y"
    {
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 1319 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 108: // space_identifier_list: space_identifier_list ID_VAL
#line 643 "D:/projects/dbclib/src/dbcparser.y"
         {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
	 }
#line 1327 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 110: // comma_identifier_list: ID_VAL
#line 650 "D:/projects/dbclib/src/dbcparser.y"
    {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1335 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 111: // comma_identifier_list: comma_identifier_list TAG_COMMA ID_VAL
#line 654 "D:/projects/dbclib/src/dbcparser.y"
    {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1343 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 112: // comma_string_list: STRING_VAL
#line 660 "D:/projects/dbclib/src/dbcparser.y"
    {
        scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1351 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 113: // comma_string_list: comma_string_list TAG_COMMA STRING_VAL
#line 664 "D:/projects/dbclib/src/dbcparser.y"
        {
    	scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1359 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 114: // double_val: DOUBLE_VAL
#line 672 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < double > () = yystack_[0].value.as < double > (); }
#line 1365 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 115: // double_val: TAG_NAN
#line 673 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < double > () = std::numeric_limits<double>::quiet_NaN(); }
#line 1371 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 116: // double_val: INT_VAL
#line 674 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < double > () = static_cast<double>(yystack_[0].value.as < int64_t > ()); }
#line 1377 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 117: // little_endian: INT_VAL
#line 677 "D:/projects/dbclib/src/dbcparser.y"
                       { yylhs.value.as < bool > () = yystack_[0].value.as < int64_t > () == 1; }
#line 1383 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 118: // signedness: TAG_PLUS
#line 680 "D:/projects/dbclib/src/dbcparser.y"
               { yylhs.value.as < SignalDataType > () = SignalDataType::UnsignedData; }
#line 1389 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 119: // signedness: TAG_MINUS
#line 681 "D:/projects/dbclib/src/dbcparser.y"
                { yylhs.value.as < SignalDataType > () = SignalDataType::SignedData; }
#line 1395 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 121: // space_node_list: space_node_list ID_VAL
#line 689 "D:/projects/dbclib/src/dbcparser.y"
{
	scanner.AddToStringList( yystack_[0].value.as < std::string > () );
}
#line 1403 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 122: // node_list: TAG_BU TAG_COLON space_node_list
#line 694 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1419 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 125: // valtable: TAG_VAL_TABLE ID_VAL val_map TAG_SEMICOLON
#line 713 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& list = scanner.EnumList();
		auto& network = scanner.GetNetwork();
		network.AddValueTable(yystack_[2].value.as < std::string > (), list );
		scanner.ResetTempList();
	}
#line 1430 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 129: // signal_group: TAG_SIG_GROUP INT_VAL ID_VAL INT_VAL TAG_COLON signal_name_list TAG_SEMICOLON
#line 730 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1446 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 134: // extended_mux: TAG_SG_MUL_VAL INT_VAL ID_VAL ID_VAL value_range_list TAG_SEMICOLON
#line 758 "D:/projects/dbclib/src/dbcparser.y"
    {
        auto& network = scanner.GetNetwork();
        auto* signal = network.GetSignal(static_cast<uint64_t>(yystack_[4].value.as < int64_t > ()), yystack_[3].value.as < std::string > ());
        if (signal != nullptr) {
            auto& mux = signal->GetExtendedMux();
            mux.multiplexor = yystack_[2].value.as < std::string > ();
            const auto& list = scanner.RangeList();
            mux.range_list = list;
        }
        scanner.ResetTempList();
    }
#line 1462 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 137: // value_range: INT_VAL INT_VAL
#line 777 "D:/projects/dbclib/src/dbcparser.y"
    {
        const auto low = static_cast<size_t>(yystack_[1].value.as < int64_t > ());
        const auto high = static_cast<size_t>(-yystack_[0].value.as < int64_t > ()); /* Solves the integer problem) */
        scanner.AddToRangeList(low, high);
    }
#line 1472 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 138: // message_transmitters: TAG_BO_TX_BU INT_VAL TAG_COLON comma_identifier_list TAG_SEMICOLON
#line 785 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1488 "D:/projects/dbclib/src/dbcparser.cpp"
    break;


#line 1492 "D:/projects/dbclib/src/dbcparser.cpp"

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

#if DDDEBUG || 0
  const char *
  DbcParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if DDDEBUG || 0









  const short DbcParser::yypact_ninf_ = -253;

  const signed char DbcParser::yytable_ninf_ = -1;

  const short
  DbcParser::yypact_[] =
  {
       1,   -23,    43,    30,  -253,  -253,    59,    54,   133,    68,
      55,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,   133,
    -253,    15,    71,  -253,  -253,    72,  -253,    39,    20,    21,
      23,    -5,  -253,    67,  -253,    26,    27,    28,  -253,    40,
    -253,    29,    32,    78,    26,    34,    80,    73,  -253,    74,
    -253,  -253,  -253,  -253,    89,    38,    44,  -253,    46,  -253,
      64,    45,  -253,    19,    49,    93,    50,  -253,    75,    51,
    -253,    52,  -253,    95,    53,    96,    -6,    -9,  -253,  -253,
    -253,    56,   100,    57,    58,    62,    63,    69,   106,    42,
    -253,   -29,  -253,    88,  -253,    47,  -253,    60,   108,   -28,
     115,    66,    70,    76,    77,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,    79,  -253,    81,   -32,     2,    82,  -253,  -253,
    -253,   121,  -253,   116,   124,    85,   125,   -10,    86,  -253,
      41,   127,   129,    87,   -28,    90,    91,   131,   132,   -28,
    -253,  -253,   135,  -253,    92,   126,    94,  -253,  -253,  -253,
     140,   101,   -12,   128,  -253,   111,  -253,  -253,  -253,   130,
     -28,  -253,    24,   134,  -253,   136,   141,  -253,   -17,   -17,
     137,  -253,   139,    26,   142,   143,   156,  -253,   180,   181,
    -253,   144,   183,  -253,    61,   145,   185,   186,   -17,   173,
     192,    26,   146,    48,  -253,   158,  -253,  -253,  -253,  -253,
    -253,  -253,   189,   -28,  -253,  -253,   199,   147,  -253,   202,
     203,   150,   153,   152,  -253,   174,   -28,   155,  -253,   159,
    -253,  -253,   160,   161,   164,   163,  -253,   166,   198,   162,
     -17,   212,   218,   220,   168,   167,  -253,   -28,    38,   222,
    -253,  -253,   169,   170,   175,   217,    25,  -253,   226,   229,
     177,   225,  -253,  -253,  -253,   178,   -28,   231,   182,   179,
       0,  -253,   234,  -253,  -253,  -253,  -253,  -253,   -28,   230,
     184,    38,   232
  };

  const unsigned char
  DbcParser::yydefact_[] =
  {
       0,     0,     0,     4,     3,     1,     0,   126,     5,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,     6,
       7,   127,     0,   123,     8,     0,   120,    98,     0,   122,
       0,   139,   124,     0,   121,    85,     0,     0,   101,   139,
      37,     0,     0,     0,    85,     0,     0,    99,   140,    40,
     128,    87,   125,    86,     0,   109,     0,   102,     0,    38,
      91,     0,   110,     0,   104,     0,     0,    41,    62,     0,
     138,     0,   105,     0,     0,     0,     0,    53,    92,   100,
     111,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      67,     0,    68,    59,    63,     0,    64,     0,     0,     0,
       0,     0,     0,     0,     0,    93,    76,    75,    77,    78,
      79,    80,     0,    54,    81,     0,     0,     0,   115,   116,
     114,     0,    42,     0,     0,     0,     0,     0,     0,    60,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,    95,     0,    94,     0,     0,     0,    51,    50,    52,
       0,     0,     0,     0,    46,    43,    82,    66,    65,     0,
       0,   112,     0,     0,    71,     0,     0,    97,     0,     0,
       0,    55,     0,    85,     0,     0,    88,    44,     0,     0,
      72,     0,     0,   117,     0,     0,     0,     0,     0,     0,
       0,    85,     0,     0,    47,   130,    69,    70,   113,    73,
     118,   119,     0,     0,    57,    56,     0,     0,    84,     0,
       0,     0,     0,     0,    89,   132,     0,     0,    58,     0,
      83,    45,     0,     0,     0,     0,   131,     2,     0,     0,
       0,     0,     0,     0,     0,     0,   133,     0,   109,     0,
      49,    48,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,    39,    90,   107,     0,     0,     0,   106,     0,
       0,   135,     0,   129,   108,   137,   134,   136,     0,     0,
       0,   109,   103
  };

  const short
  DbcParser::yypgoto_[] =
  {
    -253,  -253,  -253,  -253,  -253,   204,  -253,  -253,  -253,  -253,
      83,  -253,  -253,  -253,  -186,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,   -63,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -252,
    -253,  -135,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,   -38,  -253,   187
  };

  const short
  DbcParser::yydefgoto_[] =
  {
       0,     2,     3,     7,    39,    40,    69,    79,    80,    87,
     174,   175,   196,   214,   170,   113,   133,   134,   149,    97,
     114,   115,   116,   117,   150,   176,    63,    64,   215,   234,
      88,    98,    51,    58,    67,    77,    93,   277,   278,    83,
     182,   141,   204,   222,    49,    43,    47,    52,    10,   246,
     235,   247,   256,   280,   281,    59,    60
  };

  const short
  DbcParser::yytable_[] =
  {
     152,    73,   206,   207,   286,   164,   266,   165,   166,   104,
      56,   105,   106,   107,   109,     1,   130,   138,   131,   180,
     110,   138,   226,    90,   186,   151,   139,   140,   200,   272,
     139,   140,    91,   111,     4,   112,    57,   201,    91,   292,
     167,   168,   169,     5,   193,   199,   194,   167,   168,   169,
       6,   108,   153,   154,   155,   156,   157,   126,   279,   127,
     128,   129,     8,   231,   259,   232,   172,   173,   220,   221,
       9,    41,    42,    45,    46,    48,    50,    54,    53,    55,
      61,    57,    72,    75,    62,    65,    66,    70,   237,    71,
      74,    76,    81,    78,    82,    86,    94,    96,   101,   103,
      84,   248,    85,    89,   135,    92,    95,    99,   100,   119,
     125,   102,   132,   137,   118,   120,   121,   136,   122,   142,
     160,   123,   265,   143,   148,   124,   159,   144,   161,   163,
     210,   177,   145,   178,   146,   184,   147,   173,   185,   187,
     158,   282,   162,   171,   191,   179,   192,   181,   229,   183,
     188,   205,   190,   289,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   189,   213,   216,   217,   195,   219,   198,   224,
     225,   227,   202,   208,   203,   209,   228,   233,   211,   212,
     236,   218,   223,   238,   230,   239,   240,   241,   242,   243,
     244,   257,   245,   249,   255,   250,   260,   258,   251,   252,
     253,   254,   261,   262,   263,   264,   267,   268,   269,   271,
     273,   270,   274,   275,   276,   283,   279,   285,   284,   288,
     290,   291,   287,    44,     0,    91,    68,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   197
  };

  const short
  DbcParser::yycheck_[] =
  {
     135,    64,   188,   189,     4,    15,   258,    17,    18,    15,
      15,    17,    18,    19,    23,    14,    45,    49,    47,   154,
      29,    49,   208,     4,   159,    57,    58,    59,     4,     4,
      58,    59,    13,    42,    57,    44,    41,    13,    13,   291,
      57,    58,    59,     0,    56,   180,    58,    57,    58,    59,
      20,    57,    50,    51,    52,    53,    54,    15,    58,    17,
      18,    19,     3,    15,   250,    17,    25,    26,     7,     8,
      16,     3,    17,    58,     3,     3,    37,    56,    58,    56,
      13,    41,     4,     3,    58,    58,    58,    58,   223,    57,
      56,    18,     3,    19,    56,    31,     3,    22,     3,     3,
      56,   236,    56,    58,    57,    56,    56,    56,    56,     9,
       4,    58,    24,     5,    58,    58,    58,    57,    56,     4,
       4,    58,   257,    57,    43,    56,     5,    57,     4,     4,
     193,     4,    56,     4,    57,     4,    57,    26,     6,     4,
      58,   276,    57,    57,     4,    58,    45,    57,   211,    58,
      58,    10,    58,   288,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    56,    27,     4,     4,    58,     4,    58,     4,
       4,    18,    58,    56,    58,    56,     4,    39,    56,    56,
      11,    57,    57,     4,    58,    58,     4,     4,    58,    56,
      58,    13,    38,    58,    48,    56,     4,    55,    58,    58,
      56,    58,     4,     3,    56,    58,     4,    58,    58,    12,
       4,    56,     3,    56,     9,     4,    58,    58,    56,     5,
      10,    57,   280,    39,    -1,    13,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175
  };

  const signed char
  DbcParser::yystos_[] =
  {
       0,    14,    63,    64,    57,     0,    20,    65,     3,    16,
     110,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    66,
      67,     3,    17,   107,    67,    58,     3,   108,     3,   106,
      37,    94,   109,    58,    56,    56,    15,    41,    95,   117,
     118,    13,    58,    88,    89,    58,    58,    96,   118,    68,
      58,    57,     4,    88,    56,     3,    18,    97,    19,    69,
      70,     3,    56,   101,    56,    56,    31,    71,    92,    58,
       4,    13,    56,    98,     3,    56,    22,    81,    93,    56,
      56,     3,    58,     3,    15,    17,    18,    19,    57,    23,
      29,    42,    44,    77,    82,    83,    84,    85,    58,     9,
      58,    58,    56,    58,    56,     4,    15,    17,    18,    19,
      45,    47,    24,    78,    79,    57,    57,     5,    49,    58,
      59,   103,     4,    57,    57,    56,    57,    57,    43,    80,
      86,    57,   103,    50,    51,    52,    53,    54,    58,     5,
       4,     4,    57,     4,    15,    17,    18,    57,    58,    59,
      76,    57,    25,    26,    72,    73,    87,     4,     4,    58,
     103,    57,   102,    58,     4,     6,   103,     4,    58,    56,
      58,     4,    45,    56,    58,    58,    74,    72,    58,   103,
       4,    13,    58,    58,   104,    10,    76,    76,    56,    56,
      88,    56,    56,    27,    75,    90,     4,     4,    57,     4,
       7,     8,   105,    57,     4,     4,    76,    18,     4,    88,
      58,    15,    17,    39,    91,   112,    11,   103,     4,    58,
       4,     4,    58,    56,    58,    38,   111,   113,   103,    58,
      56,    58,    58,    56,    58,    48,   114,    13,    55,    76,
       4,     4,     3,    56,    58,   103,   101,     4,    58,    58,
      56,    12,     4,     4,     3,    56,     9,    99,   100,    58,
     115,   116,   103,     4,    56,    58,     4,   116,     5,   103,
      10,    57,   101
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


#if DDDEBUG
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


#if DDDEBUG
  const short
  DbcParser::yyrline_[] =
  {
       0,   103,   103,   124,   132,   133,   134,   137,   138,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   172,   173,   178,
     209,   210,   213,   222,   223,   226,   229,   230,   233,   234,
     238,   239,   240,   243,   244,   247,   258,   274,   290,   309,
     310,   314,   329,   330,   331,   337,   344,   353,   354,   359,
     369,   379,   387,   397,   409,   410,   411,   412,   413,   415,
     417,   423,   424,   429,   440,   450,   451,   455,   464,   465,
     476,   500,   501,   504,   510,   517,   526,   535,   546,   547,
     551,   562,   563,   567,   629,   633,   638,   641,   642,   648,
     649,   653,   659,   663,   672,   673,   674,   677,   680,   681,
     687,   688,   693,   707,   708,   712,   722,   723,   724,   729,
     744,   745,   748,   749,   752,   771,   772,   775,   783,   798,
     799
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
#endif // DDDEBUG

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

#line 6 "D:/projects/dbclib/src/dbcparser.y"
} // dbc
#line 2057 "D:/projects/dbclib/src/dbcparser.cpp"

#line 802 "D:/projects/dbclib/src/dbcparser.y"



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
