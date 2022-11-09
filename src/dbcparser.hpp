// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file D:/projects/dbclib/src/dbcparser.hpp
 ** Define the dbc::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_D_PROJECTS_DBCLIB_SRC_DBCPARSER_HPP_INCLUDED
# define YY_YY_D_PROJECTS_DBCLIB_SRC_DBCPARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 7 "D:/projects/dbclib/src/dbcparser.y"

    namespace dbc {
        class DbcScanner;
    }

#line 55 "D:/projects/dbclib/src/dbcparser.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 5 "D:/projects/dbclib/src/dbcparser.y"
namespace dbc {
#line 191 "D:/projects/dbclib/src/dbcparser.hpp"




  /// A Bison parser.
  class DbcParser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // DOUBLE_VAL
      char dummy1[sizeof (double)];

      // TAG_DUMMY_NODE_VECTOR
      // ENUM_VAL
      char dummy2[sizeof (int)];

      // INT_VAL
      char dummy3[sizeof (int64_t)];

      // ID_VAL
      // STRING_VAL
      char dummy4[sizeof (std::string)];

      // HEX_VAL
      char dummy5[sizeof (uint64_t)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    EOL = 0,                       // EOL
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    TAG_COLON = 258,               // TAG_COLON
    TAG_SEMICOLON = 259,           // TAG_SEMICOLON
    TAG_SEP = 260,                 // TAG_SEP
    TAG_AT = 261,                  // TAG_AT
    TAG_PLUS = 262,                // TAG_PLUS
    TAG_MINUS = 263,               // TAG_MINUS
    TAG_BOX_OPEN = 264,            // TAG_BOX_OPEN
    TAG_BOX_CLOSE = 265,           // TAG_BOX_CLOSE
    TAG_PAR_OPEN = 266,            // TAG_PAR_OPEN
    TAG_PAR_CLOSE = 267,           // TAG_PAR_CLOSE
    TAG_COMMA = 268,               // TAG_COMMA
    TAG_VERSION = 269,             // TAG_VERSION
    TAG_BO = 270,                  // TAG_BO
    TAG_BS = 271,                  // TAG_BS
    TAG_BU = 272,                  // TAG_BU
    TAG_SG = 273,                  // TAG_SG
    TAG_EV = 274,                  // TAG_EV
    TAG_NS = 275,                  // TAG_NS
    TAG_NS_DESC = 276,             // TAG_NS_DESC
    TAG_CM = 277,                  // TAG_CM
    TAG_BA_DEF = 278,              // TAG_BA_DEF
    TAG_BA = 279,                  // TAG_BA
    TAG_VAL = 280,                 // TAG_VAL
    TAG_CAT_DEF = 281,             // TAG_CAT_DEF
    TAG_CAT = 282,                 // TAG_CAT
    TAG_FILTER = 283,              // TAG_FILTER
    TAG_BA_DEF_DEF = 284,          // TAG_BA_DEF_DEF
    TAG_EV_DATA = 285,             // TAG_EV_DATA
    TAG_ENVVAR_DATA = 286,         // TAG_ENVVAR_DATA
    TAG_SGTYPE = 287,              // TAG_SGTYPE
    TAG_SGTYPE_VAL = 288,          // TAG_SGTYPE_VAL
    TAG_BA_DEF_SGTYPE = 289,       // TAG_BA_DEF_SGTYPE
    TAG_BA_SGTYPE = 290,           // TAG_BA_SGTYPE
    TAG_SIG_TYPE_REF = 291,        // TAG_SIG_TYPE_REF
    TAG_VAL_TABLE = 292,           // TAG_VAL_TABLE
    TAG_SIG_GROUP = 293,           // TAG_SIG_GROUP
    TAG_SIG_VALTYPE = 294,         // TAG_SIG_VALTYPE
    TAG_SIGTYPE_VALTYPE = 295,     // TAG_SIGTYPE_VALTYPE
    TAG_BO_TX_BU = 296,            // TAG_BO_TX_BU
    TAG_BA_DEF_REL = 297,          // TAG_BA_DEF_REL
    TAG_BA_REL = 298,              // TAG_BA_REL
    TAG_BA_DEF_DEF_REL = 299,      // TAG_BA_DEF_DEF_REL
    TAG_BU_SG_REL = 300,           // TAG_BU_SG_REL
    TAG_BU_EV_REL = 301,           // TAG_BU_EV_REL
    TAG_BU_BO_REL = 302,           // TAG_BU_BO_REL
    TAG_SG_MUL_VAL = 303,          // TAG_SG_MUL_VAL
    TAG_NAN = 304,                 // TAG_NAN
    TAG_INT = 305,                 // TAG_INT
    TAG_FLOAT = 306,               // TAG_FLOAT
    TAG_ENUM = 307,                // TAG_ENUM
    TAG_HEX = 308,                 // TAG_HEX
    TAG_STRING = 309,              // TAG_STRING
    TAG_DUMMY_NODE_VECTOR = 310,   // TAG_DUMMY_NODE_VECTOR
    ID_VAL = 311,                  // ID_VAL
    STRING_VAL = 312,              // STRING_VAL
    INT_VAL = 313,                 // INT_VAL
    DOUBLE_VAL = 314,              // DOUBLE_VAL
    ENUM_VAL = 315,                // ENUM_VAL
    HEX_VAL = 316                  // HEX_VAL
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 62, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // EOL
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TAG_COLON = 3,                         // TAG_COLON
        S_TAG_SEMICOLON = 4,                     // TAG_SEMICOLON
        S_TAG_SEP = 5,                           // TAG_SEP
        S_TAG_AT = 6,                            // TAG_AT
        S_TAG_PLUS = 7,                          // TAG_PLUS
        S_TAG_MINUS = 8,                         // TAG_MINUS
        S_TAG_BOX_OPEN = 9,                      // TAG_BOX_OPEN
        S_TAG_BOX_CLOSE = 10,                    // TAG_BOX_CLOSE
        S_TAG_PAR_OPEN = 11,                     // TAG_PAR_OPEN
        S_TAG_PAR_CLOSE = 12,                    // TAG_PAR_CLOSE
        S_TAG_COMMA = 13,                        // TAG_COMMA
        S_TAG_VERSION = 14,                      // TAG_VERSION
        S_TAG_BO = 15,                           // TAG_BO
        S_TAG_BS = 16,                           // TAG_BS
        S_TAG_BU = 17,                           // TAG_BU
        S_TAG_SG = 18,                           // TAG_SG
        S_TAG_EV = 19,                           // TAG_EV
        S_TAG_NS = 20,                           // TAG_NS
        S_TAG_NS_DESC = 21,                      // TAG_NS_DESC
        S_TAG_CM = 22,                           // TAG_CM
        S_TAG_BA_DEF = 23,                       // TAG_BA_DEF
        S_TAG_BA = 24,                           // TAG_BA
        S_TAG_VAL = 25,                          // TAG_VAL
        S_TAG_CAT_DEF = 26,                      // TAG_CAT_DEF
        S_TAG_CAT = 27,                          // TAG_CAT
        S_TAG_FILTER = 28,                       // TAG_FILTER
        S_TAG_BA_DEF_DEF = 29,                   // TAG_BA_DEF_DEF
        S_TAG_EV_DATA = 30,                      // TAG_EV_DATA
        S_TAG_ENVVAR_DATA = 31,                  // TAG_ENVVAR_DATA
        S_TAG_SGTYPE = 32,                       // TAG_SGTYPE
        S_TAG_SGTYPE_VAL = 33,                   // TAG_SGTYPE_VAL
        S_TAG_BA_DEF_SGTYPE = 34,                // TAG_BA_DEF_SGTYPE
        S_TAG_BA_SGTYPE = 35,                    // TAG_BA_SGTYPE
        S_TAG_SIG_TYPE_REF = 36,                 // TAG_SIG_TYPE_REF
        S_TAG_VAL_TABLE = 37,                    // TAG_VAL_TABLE
        S_TAG_SIG_GROUP = 38,                    // TAG_SIG_GROUP
        S_TAG_SIG_VALTYPE = 39,                  // TAG_SIG_VALTYPE
        S_TAG_SIGTYPE_VALTYPE = 40,              // TAG_SIGTYPE_VALTYPE
        S_TAG_BO_TX_BU = 41,                     // TAG_BO_TX_BU
        S_TAG_BA_DEF_REL = 42,                   // TAG_BA_DEF_REL
        S_TAG_BA_REL = 43,                       // TAG_BA_REL
        S_TAG_BA_DEF_DEF_REL = 44,               // TAG_BA_DEF_DEF_REL
        S_TAG_BU_SG_REL = 45,                    // TAG_BU_SG_REL
        S_TAG_BU_EV_REL = 46,                    // TAG_BU_EV_REL
        S_TAG_BU_BO_REL = 47,                    // TAG_BU_BO_REL
        S_TAG_SG_MUL_VAL = 48,                   // TAG_SG_MUL_VAL
        S_TAG_NAN = 49,                          // TAG_NAN
        S_TAG_INT = 50,                          // TAG_INT
        S_TAG_FLOAT = 51,                        // TAG_FLOAT
        S_TAG_ENUM = 52,                         // TAG_ENUM
        S_TAG_HEX = 53,                          // TAG_HEX
        S_TAG_STRING = 54,                       // TAG_STRING
        S_TAG_DUMMY_NODE_VECTOR = 55,            // TAG_DUMMY_NODE_VECTOR
        S_ID_VAL = 56,                           // ID_VAL
        S_STRING_VAL = 57,                       // STRING_VAL
        S_INT_VAL = 58,                          // INT_VAL
        S_DOUBLE_VAL = 59,                       // DOUBLE_VAL
        S_ENUM_VAL = 60,                         // ENUM_VAL
        S_HEX_VAL = 61,                          // HEX_VAL
        S_YYACCEPT = 62,                         // $accept
        S_dbc_file = 63,                         // dbc_file
        S_version = 64,                          // version
        S_symbol_section = 65,                   // symbol_section
        S_symbol_list = 66,                      // symbol_list
        S_symbol = 67,                           // symbol
        S_envvar_list = 68,                      // envvar_list
        S_envvar = 69,                           // envvar
        S_envvar_data_list = 70,                 // envvar_data_list
        S_envvar_data = 71,                      // envvar_data
        S_category_definition_list = 72,         // category_definition_list
        S_category_definition = 73,              // category_definition
        S_category_list = 74,                    // category_list
        S_category = 75,                         // category
        S_attribute_value = 76,                  // attribute_value
        S_attribute_list = 77,                   // attribute_list
        S_attribute = 78,                        // attribute
        S_attribute_rel_list = 79,               // attribute_rel_list
        S_attribute_rel = 80,                    // attribute_rel
        S_attribute_def_list = 81,               // attribute_def_list
        S_attribute_definition_default = 82,     // attribute_definition_default
        S_attribute_definition_object_or_relation = 83, // attribute_definition_object_or_relation
        S_attribute_definition = 84,             // attribute_definition
        S_attribute_object_type = 85,            // attribute_object_type
        S_val_list = 86,                         // val_list
        S_val = 87,                              // val
        S_val_map = 88,                          // val_map
        S_val_map_entry = 89,                    // val_map_entry
        S_sig_valtype_list = 90,                 // sig_valtype_list
        S_sig_valtype = 91,                      // sig_valtype
        S_comment_list = 92,                     // comment_list
        S_comment = 93,                          // comment
        S_message_list = 94,                     // message_list
        S_message = 95,                          // message
        S_signal_list = 96,                      // signal_list
        S_signal = 97,                           // signal
        S_mux_info = 98,                         // mux_info
        S_signal_name_list = 99,                 // signal_name_list
        S_space_identifier_list = 100,           // space_identifier_list
        S_comma_identifier_list = 101,           // comma_identifier_list
        S_comma_string_list = 102,               // comma_string_list
        S_double_val = 103,                      // double_val
        S_little_endian = 104,                   // little_endian
        S_signedness = 105,                      // signedness
        S_space_node_list = 106,                 // space_node_list
        S_node_list = 107,                       // node_list
        S_valtable_list = 108,                   // valtable_list
        S_valtable = 109,                        // valtable
        S_message_section = 110,                 // message_section
        S_signal_group = 111,                    // signal_group
        S_signal_group_list = 112,               // signal_group_list
        S_extended_mux_list = 113,               // extended_mux_list
        S_extended_mux = 114,                    // extended_mux
        S_value_range_list = 115,                // value_range_list
        S_value_range = 116,                     // value_range
        S_message_transmitters = 117,            // message_transmitters
        S_message_transmitter_list = 118         // message_transmitter_list
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.move< int64_t > (std::move (that.value));
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.move< uint64_t > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int64_t&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int64_t& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, uint64_t&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const uint64_t& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_DOUBLE_VAL: // DOUBLE_VAL
        value.template destroy< double > ();
        break;

      case symbol_kind::S_TAG_DUMMY_NODE_VECTOR: // TAG_DUMMY_NODE_VECTOR
      case symbol_kind::S_ENUM_VAL: // ENUM_VAL
        value.template destroy< int > ();
        break;

      case symbol_kind::S_INT_VAL: // INT_VAL
        value.template destroy< int64_t > ();
        break;

      case symbol_kind::S_ID_VAL: // ID_VAL
      case symbol_kind::S_STRING_VAL: // STRING_VAL
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_HEX_VAL: // HEX_VAL
        value.template destroy< uint64_t > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return DbcParser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const double& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const int& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int64_t v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const int64_t& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::string& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, uint64_t v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const uint64_t& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    DbcParser (dbc::DbcScanner &scanner_yyarg);
    virtual ~DbcParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    DbcParser (const DbcParser&) = delete;
    /// Non copyable.
    DbcParser& operator= (const DbcParser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0


    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EOL ()
      {
        return symbol_type (token::EOL);
      }
#else
      static
      symbol_type
      make_EOL ()
      {
        return symbol_type (token::EOL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_COLON ()
      {
        return symbol_type (token::TAG_COLON);
      }
#else
      static
      symbol_type
      make_TAG_COLON ()
      {
        return symbol_type (token::TAG_COLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SEMICOLON ()
      {
        return symbol_type (token::TAG_SEMICOLON);
      }
#else
      static
      symbol_type
      make_TAG_SEMICOLON ()
      {
        return symbol_type (token::TAG_SEMICOLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SEP ()
      {
        return symbol_type (token::TAG_SEP);
      }
#else
      static
      symbol_type
      make_TAG_SEP ()
      {
        return symbol_type (token::TAG_SEP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_AT ()
      {
        return symbol_type (token::TAG_AT);
      }
#else
      static
      symbol_type
      make_TAG_AT ()
      {
        return symbol_type (token::TAG_AT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_PLUS ()
      {
        return symbol_type (token::TAG_PLUS);
      }
#else
      static
      symbol_type
      make_TAG_PLUS ()
      {
        return symbol_type (token::TAG_PLUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_MINUS ()
      {
        return symbol_type (token::TAG_MINUS);
      }
#else
      static
      symbol_type
      make_TAG_MINUS ()
      {
        return symbol_type (token::TAG_MINUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BOX_OPEN ()
      {
        return symbol_type (token::TAG_BOX_OPEN);
      }
#else
      static
      symbol_type
      make_TAG_BOX_OPEN ()
      {
        return symbol_type (token::TAG_BOX_OPEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BOX_CLOSE ()
      {
        return symbol_type (token::TAG_BOX_CLOSE);
      }
#else
      static
      symbol_type
      make_TAG_BOX_CLOSE ()
      {
        return symbol_type (token::TAG_BOX_CLOSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_PAR_OPEN ()
      {
        return symbol_type (token::TAG_PAR_OPEN);
      }
#else
      static
      symbol_type
      make_TAG_PAR_OPEN ()
      {
        return symbol_type (token::TAG_PAR_OPEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_PAR_CLOSE ()
      {
        return symbol_type (token::TAG_PAR_CLOSE);
      }
#else
      static
      symbol_type
      make_TAG_PAR_CLOSE ()
      {
        return symbol_type (token::TAG_PAR_CLOSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_COMMA ()
      {
        return symbol_type (token::TAG_COMMA);
      }
#else
      static
      symbol_type
      make_TAG_COMMA ()
      {
        return symbol_type (token::TAG_COMMA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_VERSION ()
      {
        return symbol_type (token::TAG_VERSION);
      }
#else
      static
      symbol_type
      make_TAG_VERSION ()
      {
        return symbol_type (token::TAG_VERSION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BO ()
      {
        return symbol_type (token::TAG_BO);
      }
#else
      static
      symbol_type
      make_TAG_BO ()
      {
        return symbol_type (token::TAG_BO);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BS ()
      {
        return symbol_type (token::TAG_BS);
      }
#else
      static
      symbol_type
      make_TAG_BS ()
      {
        return symbol_type (token::TAG_BS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BU ()
      {
        return symbol_type (token::TAG_BU);
      }
#else
      static
      symbol_type
      make_TAG_BU ()
      {
        return symbol_type (token::TAG_BU);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SG ()
      {
        return symbol_type (token::TAG_SG);
      }
#else
      static
      symbol_type
      make_TAG_SG ()
      {
        return symbol_type (token::TAG_SG);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_EV ()
      {
        return symbol_type (token::TAG_EV);
      }
#else
      static
      symbol_type
      make_TAG_EV ()
      {
        return symbol_type (token::TAG_EV);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_NS ()
      {
        return symbol_type (token::TAG_NS);
      }
#else
      static
      symbol_type
      make_TAG_NS ()
      {
        return symbol_type (token::TAG_NS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_NS_DESC ()
      {
        return symbol_type (token::TAG_NS_DESC);
      }
#else
      static
      symbol_type
      make_TAG_NS_DESC ()
      {
        return symbol_type (token::TAG_NS_DESC);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_CM ()
      {
        return symbol_type (token::TAG_CM);
      }
#else
      static
      symbol_type
      make_TAG_CM ()
      {
        return symbol_type (token::TAG_CM);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA_DEF ()
      {
        return symbol_type (token::TAG_BA_DEF);
      }
#else
      static
      symbol_type
      make_TAG_BA_DEF ()
      {
        return symbol_type (token::TAG_BA_DEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA ()
      {
        return symbol_type (token::TAG_BA);
      }
#else
      static
      symbol_type
      make_TAG_BA ()
      {
        return symbol_type (token::TAG_BA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_VAL ()
      {
        return symbol_type (token::TAG_VAL);
      }
#else
      static
      symbol_type
      make_TAG_VAL ()
      {
        return symbol_type (token::TAG_VAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_CAT_DEF ()
      {
        return symbol_type (token::TAG_CAT_DEF);
      }
#else
      static
      symbol_type
      make_TAG_CAT_DEF ()
      {
        return symbol_type (token::TAG_CAT_DEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_CAT ()
      {
        return symbol_type (token::TAG_CAT);
      }
#else
      static
      symbol_type
      make_TAG_CAT ()
      {
        return symbol_type (token::TAG_CAT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_FILTER ()
      {
        return symbol_type (token::TAG_FILTER);
      }
#else
      static
      symbol_type
      make_TAG_FILTER ()
      {
        return symbol_type (token::TAG_FILTER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA_DEF_DEF ()
      {
        return symbol_type (token::TAG_BA_DEF_DEF);
      }
#else
      static
      symbol_type
      make_TAG_BA_DEF_DEF ()
      {
        return symbol_type (token::TAG_BA_DEF_DEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_EV_DATA ()
      {
        return symbol_type (token::TAG_EV_DATA);
      }
#else
      static
      symbol_type
      make_TAG_EV_DATA ()
      {
        return symbol_type (token::TAG_EV_DATA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_ENVVAR_DATA ()
      {
        return symbol_type (token::TAG_ENVVAR_DATA);
      }
#else
      static
      symbol_type
      make_TAG_ENVVAR_DATA ()
      {
        return symbol_type (token::TAG_ENVVAR_DATA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SGTYPE ()
      {
        return symbol_type (token::TAG_SGTYPE);
      }
#else
      static
      symbol_type
      make_TAG_SGTYPE ()
      {
        return symbol_type (token::TAG_SGTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SGTYPE_VAL ()
      {
        return symbol_type (token::TAG_SGTYPE_VAL);
      }
#else
      static
      symbol_type
      make_TAG_SGTYPE_VAL ()
      {
        return symbol_type (token::TAG_SGTYPE_VAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA_DEF_SGTYPE ()
      {
        return symbol_type (token::TAG_BA_DEF_SGTYPE);
      }
#else
      static
      symbol_type
      make_TAG_BA_DEF_SGTYPE ()
      {
        return symbol_type (token::TAG_BA_DEF_SGTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA_SGTYPE ()
      {
        return symbol_type (token::TAG_BA_SGTYPE);
      }
#else
      static
      symbol_type
      make_TAG_BA_SGTYPE ()
      {
        return symbol_type (token::TAG_BA_SGTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SIG_TYPE_REF ()
      {
        return symbol_type (token::TAG_SIG_TYPE_REF);
      }
#else
      static
      symbol_type
      make_TAG_SIG_TYPE_REF ()
      {
        return symbol_type (token::TAG_SIG_TYPE_REF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_VAL_TABLE ()
      {
        return symbol_type (token::TAG_VAL_TABLE);
      }
#else
      static
      symbol_type
      make_TAG_VAL_TABLE ()
      {
        return symbol_type (token::TAG_VAL_TABLE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SIG_GROUP ()
      {
        return symbol_type (token::TAG_SIG_GROUP);
      }
#else
      static
      symbol_type
      make_TAG_SIG_GROUP ()
      {
        return symbol_type (token::TAG_SIG_GROUP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SIG_VALTYPE ()
      {
        return symbol_type (token::TAG_SIG_VALTYPE);
      }
#else
      static
      symbol_type
      make_TAG_SIG_VALTYPE ()
      {
        return symbol_type (token::TAG_SIG_VALTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SIGTYPE_VALTYPE ()
      {
        return symbol_type (token::TAG_SIGTYPE_VALTYPE);
      }
#else
      static
      symbol_type
      make_TAG_SIGTYPE_VALTYPE ()
      {
        return symbol_type (token::TAG_SIGTYPE_VALTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BO_TX_BU ()
      {
        return symbol_type (token::TAG_BO_TX_BU);
      }
#else
      static
      symbol_type
      make_TAG_BO_TX_BU ()
      {
        return symbol_type (token::TAG_BO_TX_BU);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA_DEF_REL ()
      {
        return symbol_type (token::TAG_BA_DEF_REL);
      }
#else
      static
      symbol_type
      make_TAG_BA_DEF_REL ()
      {
        return symbol_type (token::TAG_BA_DEF_REL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA_REL ()
      {
        return symbol_type (token::TAG_BA_REL);
      }
#else
      static
      symbol_type
      make_TAG_BA_REL ()
      {
        return symbol_type (token::TAG_BA_REL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BA_DEF_DEF_REL ()
      {
        return symbol_type (token::TAG_BA_DEF_DEF_REL);
      }
#else
      static
      symbol_type
      make_TAG_BA_DEF_DEF_REL ()
      {
        return symbol_type (token::TAG_BA_DEF_DEF_REL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BU_SG_REL ()
      {
        return symbol_type (token::TAG_BU_SG_REL);
      }
#else
      static
      symbol_type
      make_TAG_BU_SG_REL ()
      {
        return symbol_type (token::TAG_BU_SG_REL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BU_EV_REL ()
      {
        return symbol_type (token::TAG_BU_EV_REL);
      }
#else
      static
      symbol_type
      make_TAG_BU_EV_REL ()
      {
        return symbol_type (token::TAG_BU_EV_REL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_BU_BO_REL ()
      {
        return symbol_type (token::TAG_BU_BO_REL);
      }
#else
      static
      symbol_type
      make_TAG_BU_BO_REL ()
      {
        return symbol_type (token::TAG_BU_BO_REL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_SG_MUL_VAL ()
      {
        return symbol_type (token::TAG_SG_MUL_VAL);
      }
#else
      static
      symbol_type
      make_TAG_SG_MUL_VAL ()
      {
        return symbol_type (token::TAG_SG_MUL_VAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_NAN ()
      {
        return symbol_type (token::TAG_NAN);
      }
#else
      static
      symbol_type
      make_TAG_NAN ()
      {
        return symbol_type (token::TAG_NAN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_INT ()
      {
        return symbol_type (token::TAG_INT);
      }
#else
      static
      symbol_type
      make_TAG_INT ()
      {
        return symbol_type (token::TAG_INT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_FLOAT ()
      {
        return symbol_type (token::TAG_FLOAT);
      }
#else
      static
      symbol_type
      make_TAG_FLOAT ()
      {
        return symbol_type (token::TAG_FLOAT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_ENUM ()
      {
        return symbol_type (token::TAG_ENUM);
      }
#else
      static
      symbol_type
      make_TAG_ENUM ()
      {
        return symbol_type (token::TAG_ENUM);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_HEX ()
      {
        return symbol_type (token::TAG_HEX);
      }
#else
      static
      symbol_type
      make_TAG_HEX ()
      {
        return symbol_type (token::TAG_HEX);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_STRING ()
      {
        return symbol_type (token::TAG_STRING);
      }
#else
      static
      symbol_type
      make_TAG_STRING ()
      {
        return symbol_type (token::TAG_STRING);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TAG_DUMMY_NODE_VECTOR (int v)
      {
        return symbol_type (token::TAG_DUMMY_NODE_VECTOR, std::move (v));
      }
#else
      static
      symbol_type
      make_TAG_DUMMY_NODE_VECTOR (const int& v)
      {
        return symbol_type (token::TAG_DUMMY_NODE_VECTOR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID_VAL (std::string v)
      {
        return symbol_type (token::ID_VAL, std::move (v));
      }
#else
      static
      symbol_type
      make_ID_VAL (const std::string& v)
      {
        return symbol_type (token::ID_VAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_VAL (std::string v)
      {
        return symbol_type (token::STRING_VAL, std::move (v));
      }
#else
      static
      symbol_type
      make_STRING_VAL (const std::string& v)
      {
        return symbol_type (token::STRING_VAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT_VAL (int64_t v)
      {
        return symbol_type (token::INT_VAL, std::move (v));
      }
#else
      static
      symbol_type
      make_INT_VAL (const int64_t& v)
      {
        return symbol_type (token::INT_VAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLE_VAL (double v)
      {
        return symbol_type (token::DOUBLE_VAL, std::move (v));
      }
#else
      static
      symbol_type
      make_DOUBLE_VAL (const double& v)
      {
        return symbol_type (token::DOUBLE_VAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENUM_VAL (int v)
      {
        return symbol_type (token::ENUM_VAL, std::move (v));
      }
#else
      static
      symbol_type
      make_ENUM_VAL (const int& v)
      {
        return symbol_type (token::ENUM_VAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HEX_VAL (uint64_t v)
      {
        return symbol_type (token::HEX_VAL, std::move (v));
      }
#else
      static
      symbol_type
      make_HEX_VAL (const uint64_t& v)
      {
        return symbol_type (token::HEX_VAL, v);
      }
#endif


  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    DbcParser (const DbcParser&);
    /// Non copyable.
    DbcParser& operator= (const DbcParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 272,     ///< Last index in yytable_.
      yynnts_ = 57,  ///< Number of nonterminal symbols.
      yyfinal_ = 5 ///< Termination state number.
    };


    // User arguments.
    dbc::DbcScanner &scanner;

  };


#line 5 "D:/projects/dbclib/src/dbcparser.y"
} // dbc
#line 2259 "D:/projects/dbclib/src/dbcparser.hpp"




#endif // !YY_YY_D_PROJECTS_DBCLIB_SRC_DBCPARSER_HPP_INCLUDED
