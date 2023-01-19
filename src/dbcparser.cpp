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
#line 19 "D:/projects/dbclib/src/dbcparser.y"

    #include <sstream>
    #include "dbcscanner.h"
    #include <limits>

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

#line 5 "D:/projects/dbclib/src/dbcparser.y"
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
      case symbol_kind::S_object_type: // object_type
      case symbol_kind::S_object_rel_type: // object_rel_type
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
      case symbol_kind::S_object_type: // object_type
      case symbol_kind::S_object_rel_type: // object_rel_type
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
      case symbol_kind::S_object_type: // object_type
      case symbol_kind::S_object_rel_type: // object_rel_type
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
      case symbol_kind::S_object_type: // object_type
      case symbol_kind::S_object_rel_type: // object_rel_type
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
      case symbol_kind::S_object_type: // object_type
      case symbol_kind::S_object_rel_type: // object_rel_type
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
      case symbol_kind::S_object_type: // object_type
      case symbol_kind::S_object_rel_type: // object_rel_type
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
      case symbol_kind::S_object_type: // object_type
      case symbol_kind::S_object_rel_type: // object_rel_type
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
  case 25: // version: TAG_VERSION STRING_VAL
#line 133 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
		network.Version(yystack_[0].value.as < std::string > ());
		scanner.ResetTempList();
	}
#line 889 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 58: // envvar: TAG_EV ID_VAL TAG_COLON INT_VAL TAG_BOX_OPEN double_val TAG_SEP double_val TAG_BOX_CLOSE STRING_VAL double_val INT_VAL TAG_DUMMY_NODE_VECTOR comma_identifier_list TAG_SEMICOLON
#line 192 "D:/projects/dbclib/src/dbcparser.y"
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
#line 908 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 59: // envvar_data: TAG_ENVVAR_DATA ID_VAL TAG_COLON INT_VAL TAG_SEMICOLON
#line 211 "D:/projects/dbclib/src/dbcparser.y"
          {
		/* To be defined what to do here */
		scanner.ResetTempList();
	  }
#line 917 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 63: // attribute_value: INT_VAL
#line 225 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < std::string > () = std::to_string(yystack_[0].value.as < int64_t > ()); }
#line 923 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 64: // attribute_value: STRING_VAL
#line 226 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 929 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 65: // attribute_value: DOUBLE_VAL
#line 227 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < std::string > () = std::to_string(yystack_[0].value.as < double > ()); }
#line 935 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 66: // attribute: TAG_BA STRING_VAL attribute_value TAG_SEMICOLON
#line 235 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition(yystack_[2].value.as < std::string > ());
		auto& attribute = network.CreateAttribute( definition );
		attribute.Value(yystack_[1].value.as < std::string > ());
		scanner.ResetTempList();
	  }
#line 947 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 67: // attribute: TAG_BA STRING_VAL TAG_BU ID_VAL attribute_value TAG_SEMICOLON
#line 248 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition(yystack_[4].value.as < std::string > ());
		auto* node = network.GetNode( yystack_[2].value.as < std::string > () );
		if ( node != nullptr) {
			auto& attribute = node->CreateAttribute( definition );
            attribute.Value(yystack_[1].value.as < std::string > ());
		}
		scanner.ResetTempList();
	  }
#line 962 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 68: // attribute: TAG_BA STRING_VAL TAG_BO INT_VAL attribute_value TAG_SEMICOLON
#line 264 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition(yystack_[4].value.as < std::string > ());
		auto* message = network.GetMessage( static_cast<uint64_t>(yystack_[2].value.as < int64_t > ()));
		if ( message != nullptr ) {
			auto& attribute = message->CreateAttribute( definition );
            attribute.Value(yystack_[1].value.as < std::string > ());
		}
		scanner.ResetTempList();
	  }
#line 977 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 69: // attribute: TAG_BA STRING_VAL TAG_SG INT_VAL ID_VAL attribute_value TAG_SEMICOLON
#line 281 "D:/projects/dbclib/src/dbcparser.y"
          {
		 auto& network = scanner.GetNetwork();
		 auto& definition = network.CreateDefinition(yystack_[5].value.as < std::string > ());
		 auto* signal = network.GetSignal( static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()), yystack_[2].value.as < std::string > ());
		 if ( signal != nullptr ) {
		   auto& attribute = signal->CreateAttribute( definition );
           attribute.Value(yystack_[1].value.as < std::string > ());
	     }
	     scanner.ResetTempList();
	  }
#line 992 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 70: // attribute_rel: TAG_BA_REL STRING_VAL TAG_BU_SG_REL ID_VAL TAG_SG INT_VAL ID_VAL attribute_value TAG_SEMICOLON
#line 303 "D:/projects/dbclib/src/dbcparser.y"
          {
		/* To be defined */
		scanner.ResetTempList();
	  }
#line 1001 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 71: // attribute_definition_default: attribute_definition_object_or_relation STRING_VAL double_val TAG_SEMICOLON
#line 311 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition( yystack_[2].value.as < std::string > () );
		definition.Value( yystack_[1].value.as < double > () );
		scanner.ResetTempList();
	  }
#line 1012 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 72: // attribute_definition_default: attribute_definition_object_or_relation STRING_VAL STRING_VAL TAG_SEMICOLON
#line 318 "D:/projects/dbclib/src/dbcparser.y"
          {
		auto& network = scanner.GetNetwork();
		auto& definition = network.CreateDefinition( yystack_[2].value.as < std::string > () );
		definition.Value( yystack_[1].value.as < std::string > () );
		scanner.ResetTempList();
	  }
#line 1023 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 73: // attribute_definition_object_or_relation: TAG_BA_DEF_DEF
#line 326 "D:/projects/dbclib/src/dbcparser.y"
                      { yylhs.value.as < bool > () = false; }
#line 1029 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 74: // attribute_definition_object_or_relation: TAG_BA_DEF_DEF_REL
#line 327 "D:/projects/dbclib/src/dbcparser.y"
                         { yylhs.value.as < bool > () = true; }
#line 1035 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 75: // attribute_definition: attribute_object_type STRING_VAL TAG_INT INT_VAL INT_VAL TAG_SEMICOLON
#line 332 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::IntegerValue);
		definition.Min(static_cast<double>( yystack_[2].value.as < int64_t > () ));
		definition.Max(static_cast<double>( yystack_[1].value.as < int64_t > () ));
		scanner.ResetTempList();
	  }
#line 1049 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 76: // attribute_definition: attribute_object_type STRING_VAL TAG_FLOAT double_val double_val TAG_SEMICOLON
#line 342 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::FloatValue);
		definition.Min( yystack_[2].value.as < double > () );
		definition.Max( yystack_[1].value.as < double > () );
		scanner.ResetTempList();
	  }
#line 1063 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 77: // attribute_definition: attribute_object_type STRING_VAL TAG_STRING TAG_SEMICOLON
#line 352 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( yystack_[2].value.as < std::string > () );
       	definition.Type( yystack_[3].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::StringValue);
       	scanner.ResetTempList();
	  }
#line 1075 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 78: // attribute_definition: attribute_object_type STRING_VAL TAG_ENUM comma_string_list TAG_SEMICOLON
#line 360 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( yystack_[3].value.as < std::string > () );
       	definition.Type( yystack_[4].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::EnumValue);
       	const auto& list = scanner.StringList();
        definition.EnumList(list);
		scanner.ResetTempList();
	  }
#line 1089 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 79: // attribute_definition: attribute_object_type STRING_VAL TAG_HEX INT_VAL INT_VAL TAG_SEMICOLON
#line 370 "D:/projects/dbclib/src/dbcparser.y"
          {
	    auto& network = scanner.GetNetwork();
       	auto& definition = network.CreateDefinition( yystack_[4].value.as < std::string > () );
       	definition.Type( yystack_[5].value.as < AttributeType > () );
       	definition.ValueType( AttributeValueType::HexValue);
		definition.Min(static_cast<double>( yystack_[2].value.as < int64_t > () ));
		definition.Max(static_cast<double>( yystack_[1].value.as < int64_t > () ));
		scanner.ResetTempList();
	  }
#line 1103 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 80: // attribute_object_type: TAG_BA_DEF object_type
#line 381 "D:/projects/dbclib/src/dbcparser.y"
                           {yylhs.value.as < AttributeType > () = yystack_[1].value.as< AttributeType > ();}
#line 1109 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 81: // attribute_object_type: TAG_BA_DEF_REL object_rel_type
#line 382 "D:/projects/dbclib/src/dbcparser.y"
                                     {yylhs.value.as < AttributeType > () = yystack_[1].value.as< AttributeType > ();}
#line 1115 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 82: // object_type: %empty
#line 385 "D:/projects/dbclib/src/dbcparser.y"
           { yylhs.value.as < AttributeType > () = AttributeType::DbcNetwork; }
#line 1121 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 83: // object_type: TAG_BU
#line 386 "D:/projects/dbclib/src/dbcparser.y"
               { yylhs.value.as < AttributeType > () = AttributeType::DbcNode; }
#line 1127 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 84: // object_type: TAG_BO
#line 387 "D:/projects/dbclib/src/dbcparser.y"
               { yylhs.value.as < AttributeType > () = AttributeType::DbcMessage; }
#line 1133 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 85: // object_type: TAG_SG
#line 388 "D:/projects/dbclib/src/dbcparser.y"
               { yylhs.value.as < AttributeType > () = AttributeType::DbcSignal; }
#line 1139 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 86: // object_type: TAG_EV
#line 389 "D:/projects/dbclib/src/dbcparser.y"
               { yylhs.value.as < AttributeType > () = AttributeType::EnvironmentVariable; }
#line 1145 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 87: // object_rel_type: TAG_BU_SG_REL
#line 392 "D:/projects/dbclib/src/dbcparser.y"
                  { yylhs.value.as < AttributeType > () = AttributeType::NodeSignalRelation; }
#line 1151 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 88: // object_rel_type: TAG_BU_BO_REL
#line 393 "D:/projects/dbclib/src/dbcparser.y"
                    { yylhs.value.as < AttributeType > () = AttributeType::NodeMessageRelation; }
#line 1157 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 89: // val: TAG_VAL INT_VAL ID_VAL val_map TAG_SEMICOLON
#line 397 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
	    auto* signal = network.GetSignal(static_cast<uint64_t>( yystack_[3].value.as < int64_t > () ), yystack_[2].value.as < std::string > ());
	    if (signal != nullptr) {
	        const auto& list = scanner.EnumList();
	        signal->EnumList(list);
	    }
	    scanner.ResetTempList();
	}
#line 1171 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 90: // val: TAG_VAL ID_VAL val_map TAG_SEMICOLON
#line 408 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& network = scanner.GetNetwork();
	    auto& env_var = network.GetEnvVar( yystack_[2].value.as < std::string > () );
	    const auto& list = scanner.EnumList();
	    env_var.EnumList(list);
	    scanner.ResetTempList();
	}
#line 1183 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 93: // val_map_entry: INT_VAL STRING_VAL
#line 423 "D:/projects/dbclib/src/dbcparser.y"
        {
	    scanner.AddToEnumList(yystack_[1].value.as < int64_t > (), yystack_[0].value.as < std::string > () ); /* Temp storage on network */
	}
#line 1191 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 94: // sig_valtype: TAG_SIG_VALTYPE INT_VAL ID_VAL TAG_COLON INT_VAL TAG_SEMICOLON
#line 438 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1215 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 100: // comment_network: TAG_CM STRING_VAL TAG_SEMICOLON
#line 467 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  network.Comment( yystack_[1].value.as < std::string > () );
	  scanner.ResetTempList();
    }
#line 1225 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 101: // comment_node: TAG_CM TAG_BU ID_VAL STRING_VAL TAG_SEMICOLON
#line 475 "D:/projects/dbclib/src/dbcparser.y"
    {
  	  auto& network = scanner.GetNetwork();
  	  auto* node = network.GetNode( yystack_[2].value.as < std::string > () );
  	  if ( node != nullptr ) {
  	    node->Comment( yystack_[1].value.as < std::string > () );
  	  }
  	  scanner.ResetTempList();
    }
#line 1238 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 102: // comment_message: TAG_CM TAG_BO INT_VAL STRING_VAL TAG_SEMICOLON
#line 486 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto* message = network.GetMessage( static_cast<uint64_t>(yystack_[2].value.as < int64_t > ()));
	  if ( message != nullptr ) {
	    message->Comment( yystack_[1].value.as < std::string > () );
	  }
	  scanner.ResetTempList();
    }
#line 1251 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 103: // comment_signal: TAG_CM TAG_SG INT_VAL ID_VAL STRING_VAL TAG_SEMICOLON
#line 497 "D:/projects/dbclib/src/dbcparser.y"
    {
 	  auto& network = scanner.GetNetwork();
 	  auto* signal = network.GetSignal( static_cast<uint64_t>(yystack_[3].value.as < int64_t > ()), yystack_[2].value.as < std::string > ());
 	  if ( signal != nullptr ) {
 	    signal->Comment( yystack_[1].value.as < std::string > () );
 	  }
 	  scanner.ResetTempList();
    }
#line 1264 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 104: // comment_env_var: TAG_CM TAG_EV ID_VAL STRING_VAL TAG_SEMICOLON
#line 508 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto& env_var = network.GetEnvVar(yystack_[2].value.as < std::string > ());
	  env_var.Comment(yystack_[1].value.as < std::string > ());
	  scanner.ResetTempList();
    }
#line 1275 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 106: // message: TAG_BO INT_VAL ID_VAL TAG_COLON INT_VAL ID_VAL
#line 520 "D:/projects/dbclib/src/dbcparser.y"
    {
	  auto& network = scanner.GetNetwork();
	  auto& message = network.CreateMessage(static_cast<uint64_t>(yystack_[4].value.as < int64_t > ()));
	  message.Name(yystack_[3].value.as < std::string > ());
	  message.NofBytes(static_cast<size_t>(yystack_[1].value.as < int64_t > ()));
	  message.Node(yystack_[0].value.as < std::string > ());
	  scanner.ResetTempList();
    }
#line 1288 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 109: // signal: TAG_SG ID_VAL mux_info TAG_COLON INT_VAL TAG_SEP INT_VAL TAG_AT little_endian signedness TAG_PAR_OPEN double_val TAG_COMMA double_val TAG_PAR_CLOSE TAG_BOX_OPEN double_val TAG_SEP double_val TAG_BOX_CLOSE STRING_VAL comma_identifier_list
#line 557 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1329 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 110: // mux_info: %empty
#line 598 "D:/projects/dbclib/src/dbcparser.y"
    {
	  yylhs.value.as < std::string > () = "";
    }
#line 1337 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 111: // mux_info: ID_VAL
#line 602 "D:/projects/dbclib/src/dbcparser.y"
    {
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 1345 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 114: // space_identifier_list: space_identifier_list ID_VAL
#line 611 "D:/projects/dbclib/src/dbcparser.y"
         {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
	 }
#line 1353 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 116: // comma_identifier_list: ID_VAL
#line 618 "D:/projects/dbclib/src/dbcparser.y"
    {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1361 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 117: // comma_identifier_list: comma_identifier_list TAG_COMMA ID_VAL
#line 622 "D:/projects/dbclib/src/dbcparser.y"
    {
		scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1369 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 118: // comma_string_list: STRING_VAL
#line 628 "D:/projects/dbclib/src/dbcparser.y"
    {
        scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1377 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 119: // comma_string_list: comma_string_list TAG_COMMA STRING_VAL
#line 632 "D:/projects/dbclib/src/dbcparser.y"
        {
    	scanner.AddToStringList( yystack_[0].value.as < std::string > () );
    }
#line 1385 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 120: // double_val: DOUBLE_VAL
#line 640 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < double > () = yystack_[0].value.as < double > (); }
#line 1391 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 121: // double_val: TAG_NAN
#line 641 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < double > () = std::numeric_limits<double>::quiet_NaN(); }
#line 1397 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 122: // double_val: INT_VAL
#line 642 "D:/projects/dbclib/src/dbcparser.y"
                 { yylhs.value.as < double > () = static_cast<double>(yystack_[0].value.as < int64_t > ()); }
#line 1403 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 123: // little_endian: INT_VAL
#line 645 "D:/projects/dbclib/src/dbcparser.y"
                       { yylhs.value.as < bool > () = yystack_[0].value.as < int64_t > () == 1; }
#line 1409 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 124: // signedness: TAG_PLUS
#line 648 "D:/projects/dbclib/src/dbcparser.y"
               { yylhs.value.as < SignalDataType > () = SignalDataType::UnsignedData; }
#line 1415 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 125: // signedness: TAG_MINUS
#line 649 "D:/projects/dbclib/src/dbcparser.y"
                { yylhs.value.as < SignalDataType > () = SignalDataType::SignedData; }
#line 1421 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 127: // space_node_list: space_node_list ID_VAL
#line 657 "D:/projects/dbclib/src/dbcparser.y"
{
	scanner.AddToStringList( yystack_[0].value.as < std::string > () );
}
#line 1429 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 128: // node: TAG_BU TAG_COLON space_node_list
#line 663 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1445 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 129: // valtable: TAG_VAL_TABLE ID_VAL val_map TAG_SEMICOLON
#line 679 "D:/projects/dbclib/src/dbcparser.y"
        {
	    auto& list = scanner.EnumList();
		auto& network = scanner.GetNetwork();
		network.AddValueTable(yystack_[2].value.as < std::string > (), list );
		scanner.ResetTempList();
	}
#line 1456 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 132: // signal_group: TAG_SIG_GROUP INT_VAL ID_VAL INT_VAL TAG_COLON signal_name_list TAG_SEMICOLON
#line 694 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1472 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 133: // extended_mux: TAG_SG_MUL_VAL INT_VAL ID_VAL ID_VAL value_range_list TAG_SEMICOLON
#line 713 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1488 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 136: // value_range: INT_VAL INT_VAL
#line 732 "D:/projects/dbclib/src/dbcparser.y"
    {
        const auto low = static_cast<size_t>(yystack_[1].value.as < int64_t > ());
        const auto high = static_cast<size_t>(-yystack_[0].value.as < int64_t > ()); /* Solves the integer problem) */
        scanner.AddToRangeList(low, high);
    }
#line 1498 "D:/projects/dbclib/src/dbcparser.cpp"
    break;

  case 137: // message_transmitters: TAG_BO_TX_BU INT_VAL TAG_COLON comma_identifier_list TAG_SEMICOLON
#line 740 "D:/projects/dbclib/src/dbcparser.y"
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
#line 1514 "D:/projects/dbclib/src/dbcparser.cpp"
    break;


#line 1518 "D:/projects/dbclib/src/dbcparser.cpp"

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









  const short DbcParser::yypact_ninf_ = -267;

  const signed char DbcParser::yytable_ninf_ = -1;

  const short
  DbcParser::yypact_[] =
  {
    -267,    28,    54,  -267,   -47,   -22,    37,    47,     5,    53,
      -6,    24,     6,   -41,     4,    29,  -267,    11,    19,     8,
      30,    31,    10,    15,  -267,    32,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,    25,  -267,    42,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,    44,    43,  -267,    83,
     105,    45,    48,    49,    55,   101,  -267,  -267,  -267,  -267,
    -267,   -10,    50,    56,    57,    51,    58,    84,    50,    59,
      61,   107,  -267,  -267,  -267,    73,    63,   -35,   -19,   103,
     119,   151,    99,    98,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,   105,   100,   102,   104,   106,  -267,
     108,   109,   110,  -267,  -267,  -267,   154,   112,   157,    50,
      50,   113,   114,   115,   116,   158,   117,   161,   111,   120,
     121,  -267,   166,  -267,  -267,   174,   122,   -33,   124,   125,
     175,   126,  -267,   127,   128,  -267,   178,  -267,   180,   184,
     132,   186,    -5,    -5,   135,  -267,  -267,  -267,  -267,   188,
     189,   190,   191,   192,  -267,   194,   140,  -267,    14,   181,
     142,  -267,  -267,   143,   -33,  -267,    16,   144,  -267,   147,
     148,   193,   -33,  -267,  -267,   201,  -267,   203,   204,    -5,
    -267,  -267,  -267,  -267,  -267,  -267,   205,  -267,   155,   152,
     156,     0,  -267,   208,   209,  -267,   159,   211,  -267,   214,
    -267,   160,   215,  -267,  -267,  -267,   217,   218,   163,  -267,
    -267,   167,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   168,
    -267,   -33,  -267,  -267,  -267,    -5,   219,   220,   221,   169,
     171,  -267,   223,   -33,   173,   176,  -267,    52,   177,  -267,
    -267,   222,   111,   -33,    17,   224,  -267,   -33,   226,   227,
     -33,   230,   -33,   229,   183,   111,   228
  };

  const unsigned char
  DbcParser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,    82,     0,     0,     0,     0,    73,     0,     0,     0,
       0,     0,     0,     0,    74,     0,     4,     5,     6,    12,
      13,    20,    21,    17,    18,    16,     0,    15,     0,    19,
      23,    14,    95,    96,    97,    98,    99,    10,   107,     8,
       9,     7,    22,    24,    11,    25,     0,   130,   126,     0,
      27,     0,     0,     0,     0,     0,    84,    83,    85,    86,
      80,     0,    91,     0,     0,     0,     0,     0,    91,     0,
       0,     0,    87,    88,    81,     0,     0,     0,     0,   105,
       0,     0,   128,     0,    34,    29,    30,    31,    32,    33,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    26,    27,     0,     0,     0,     0,   100,
       0,     0,     0,    64,    63,    65,     0,     0,     0,    91,
      91,     0,     0,     0,     0,     0,     0,     0,   115,     0,
       0,   121,     0,   122,   120,     0,     0,     0,     0,     0,
       0,     0,   108,     0,     0,   127,     0,    28,     0,     0,
       0,     0,     0,     0,     0,    66,    93,    90,    92,     0,
       0,     0,     0,     0,   129,     0,     0,   116,     0,     0,
       0,    72,    71,     0,     0,   118,     0,     0,    77,   110,
       0,     0,     0,   102,   101,     0,   104,     0,     0,     0,
      89,    60,    62,    61,    59,   113,     0,   137,     0,     0,
       0,     0,   134,     0,     0,    78,     0,     0,   111,     0,
     106,     0,     0,   103,    68,    67,     0,     0,   112,    94,
     117,     0,   136,   133,   135,    75,    76,   119,    79,     0,
     131,     0,    69,   132,   114,     0,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,   123,     0,     0,   124,
     125,     0,   115,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   109
  };

  const short
  DbcParser::yypgoto_[] =
  {
    -267,  -267,  -267,  -267,  -267,  -267,   118,  -267,  -267,  -267,
    -267,  -267,  -171,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,   -75,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -266,  -267,
    -157,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
      22,  -267
  };

  const short
  DbcParser::yydefgoto_[] =
  {
       0,     1,     2,    26,    27,    28,   123,   124,    29,    30,
      31,    32,   136,    33,    34,    35,    36,    37,    38,    70,
      84,    39,   138,   139,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    89,   162,   229,   237,   238,   188,   196,
     155,   267,   271,    92,    49,    50,    51,    52,    53,   221,
     222,    54
  };

  const short
  DbcParser::yytable_[] =
  {
     194,   207,   208,   145,   243,   130,   274,   131,   132,    61,
      55,    62,    63,    64,   151,    72,   151,    73,   217,   286,
     225,   276,   152,   153,   154,   153,   154,   218,     3,   226,
     218,   156,   157,   158,   159,   160,    56,   224,   236,    66,
      57,    67,    68,    69,    75,   232,    76,   133,   134,   135,
      58,    65,   133,   134,   135,    82,    60,    83,   220,   269,
     270,    59,    74,    71,   178,   179,    79,    77,     4,     5,
       6,     7,    85,     8,     9,    78,    10,    11,    12,    13,
      14,    15,    87,    16,   258,    17,    93,   144,    80,    81,
      86,    18,    19,    20,   257,    21,    22,    23,    24,    88,
      90,    91,    25,   125,   126,   129,   265,   127,   137,   142,
     148,   128,   140,   141,   143,   146,   275,   147,   149,   150,
     278,   161,   163,   281,    94,   283,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   164,   165,   166,   168,   175,   169,
     170,   177,   184,   171,   186,   173,   172,   187,   174,   176,
     191,   180,   181,   182,   183,   185,   189,   190,   192,   198,
     193,   195,   199,   197,   203,   200,   201,   202,   204,   205,
     206,   209,   210,   211,   212,   213,   214,   215,   216,   219,
     220,   223,   227,   228,   230,   233,   231,   234,   235,   239,
     241,   240,   245,   246,   242,   248,   247,   249,   250,   254,
     251,   252,   253,   255,   259,   261,   256,   262,   263,   264,
     260,   266,   272,   273,   268,   282,   280,   277,   279,   284,
     285,   218,   167,   244
  };

  const short
  DbcParser::yycheck_[] =
  {
     157,   172,   173,    78,     4,    15,   272,    17,    18,    15,
      57,    17,    18,    19,    49,    56,    49,    58,     4,   285,
       4,     4,    57,    58,    59,    58,    59,    13,     0,    13,
      13,    50,    51,    52,    53,    54,    58,   194,   209,    15,
       3,    17,    18,    19,    15,   202,    17,    57,    58,    59,
       3,    57,    57,    58,    59,    45,     3,    47,    58,     7,
       8,    56,    58,    57,   139,   140,    58,    56,    14,    15,
      16,    17,    57,    19,    20,    56,    22,    23,    24,    25,
      26,    27,    57,    29,   255,    31,     3,     3,    58,    58,
      58,    37,    38,    39,   251,    41,    42,    43,    44,    57,
      56,    58,    48,    58,    56,     4,   263,    58,    58,    58,
       3,    56,    56,    56,    56,    56,   273,    56,    45,    56,
     277,    18,     3,   280,    19,   282,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     3,    56,    58,    57,     4,    57,
      56,     4,     4,    57,     3,    56,    58,    56,    58,    57,
       4,    58,    58,    58,    58,    58,    56,    56,     4,     4,
      58,    57,    56,    58,     4,    58,    58,     9,     4,    57,
       4,    56,     4,     4,     4,     4,     4,     3,    58,    18,
      58,    58,    58,    56,    56,     4,    13,     4,     4,     4,
      58,    56,     4,     4,    58,     4,    57,     3,    58,    56,
       5,     4,     4,    56,     5,     4,    58,    58,    57,     6,
      10,    58,    55,    11,    58,     5,     9,    13,    12,    10,
      57,    13,   124,   221
  };

  const signed char
  DbcParser::yystos_[] =
  {
       0,    63,    64,     0,    14,    15,    16,    17,    19,    20,
      22,    23,    24,    25,    26,    27,    29,    31,    37,    38,
      39,    41,    42,    43,    44,    48,    65,    66,    67,    70,
      71,    72,    73,    75,    76,    77,    78,    79,    80,    83,
      86,    87,    88,    89,    90,    91,    92,    93,    94,   106,
     107,   108,   109,   110,   113,    57,    58,     3,     3,    56,
       3,    15,    17,    18,    19,    57,    15,    17,    18,    19,
      81,    57,    56,    58,    58,    15,    17,    56,    56,    58,
      58,    58,    45,    47,    82,    57,    58,    57,    57,    95,
      56,    58,   105,     3,    19,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    68,    69,    58,    56,    58,    56,     4,
      15,    17,    18,    57,    58,    59,    74,    58,    84,    85,
      56,    56,    58,    56,     3,    84,    56,    56,     3,    45,
      56,    49,    57,    58,    59,   102,    50,    51,    52,    53,
      54,    18,    96,     3,     3,    56,    58,    68,    57,    57,
      56,    57,    58,    56,    58,     4,    57,     4,    84,    84,
      58,    58,    58,    58,     4,    58,     3,    56,   100,    56,
      56,     4,     4,    58,   102,    57,   101,    58,     4,    56,
      58,    58,     9,     4,     4,    57,     4,    74,    74,    56,
       4,     4,     4,     4,     4,     3,    58,     4,    13,    18,
      58,   111,   112,    58,   102,     4,    13,    58,    56,    97,
      56,    13,   102,     4,     4,     4,    74,    98,    99,     4,
      56,    58,    58,     4,   112,     4,     4,    57,     4,     3,
      58,     5,     4,     4,    56,    56,    58,   102,    74,     5,
      10,     4,    58,    57,     6,   102,    58,   103,    58,     7,
       8,   104,    55,    11,   100,   102,     4,    13,   102,    12,
       9,   102,     5,   102,    10,    57,   100
  };

  const signed char
  DbcParser::yyr1_[] =
  {
       0,    62,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    66,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    70,    71,
      72,    73,    73,    74,    74,    74,    75,    75,    75,    75,
      76,    77,    77,    78,    78,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    81,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    86,    87,    87,    87,    87,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    95,    96,
      97,    97,    98,    99,    99,   100,   100,   100,   101,   101,
     102,   102,   102,   103,   104,   104,   105,   105,   106,   107,
     108,   108,   109,   110,   111,   111,   112,   113
  };

  const signed char
  DbcParser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,    15,     5,
       5,     5,     5,     1,     1,     1,     4,     6,     6,     7,
       9,     4,     4,     1,     1,     6,     6,     4,     5,     6,
       2,     2,     0,     1,     1,     1,     1,     1,     1,     5,
       4,     0,     2,     2,     6,     1,     1,     1,     1,     1,
       3,     5,     5,     6,     5,     2,     6,     0,     2,    22,
       0,     1,     1,     0,     2,     0,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     2,     3,     4,
       2,     7,     7,     6,     1,     2,     2,     5
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
  "ENUM_VAL", "HEX_VAL", "$accept", "dbc_file", "dbc_key_list", "dbc_key",
  "version", "symbol_section", "symbol_list", "symbol", "envvar",
  "envvar_data", "category_definition", "category", "attribute_value",
  "attribute", "attribute_rel", "attribute_definition_default",
  "attribute_definition_object_or_relation", "attribute_definition",
  "attribute_object_type", "object_type", "object_rel_type", "val",
  "val_map", "val_map_entry", "sig_valtype", "comment_tag",
  "comment_network", "comment_node", "comment_message", "comment_signal",
  "comment_env_var", "message_list", "message", "signal_list", "signal",
  "mux_info", "signal_name_list", "space_identifier_list",
  "comma_identifier_list", "comma_string_list", "double_val",
  "little_endian", "signedness", "space_node_list", "node", "valtable",
  "bus_speed", "signal_group", "extended_mux", "value_range_list",
  "value_range", "message_transmitters", YY_NULLPTR
  };
#endif


#if DDDEBUG
  const short
  DbcParser::yyrline_[] =
  {
       0,   104,   104,   106,   107,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   132,   140,   142,   143,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   177,   208,
     217,   220,   221,   225,   226,   227,   231,   242,   258,   274,
     294,   310,   317,   326,   327,   331,   341,   351,   359,   369,
     381,   382,   385,   386,   387,   388,   389,   392,   393,   396,
     407,   417,   418,   422,   437,   459,   460,   461,   462,   463,
     466,   474,   485,   496,   507,   516,   519,   530,   531,   535,
     597,   601,   606,   609,   610,   616,   617,   621,   627,   631,
     640,   641,   642,   645,   648,   649,   655,   656,   662,   678,
     688,   689,   693,   707,   726,   727,   730,   738
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

#line 5 "D:/projects/dbclib/src/dbcparser.y"
} // dbc
#line 2073 "D:/projects/dbclib/src/dbcparser.cpp"

#line 752 "D:/projects/dbclib/src/dbcparser.y"



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
