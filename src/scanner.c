#include "tree_sitter/parser.h"

#include <wctype.h>

enum TokenType {
    L,
    CLASS_IDENTIFIER,
};

void *tree_sitter_smali_external_scanner_create() { return NULL; }

void tree_sitter_smali_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_smali_external_scanner_serialize(void *payload, char *buffer) { return 0; }

void tree_sitter_smali_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {}

static void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

static void skip(TSLexer *lexer) { lexer->advance(lexer, true); }

static bool is_simple_name_char(int32_t c) {
    return iswalnum(c) || c == '_' || c == '-' || c == '$' ||
           (c >= 0x00a1 && c <= 0x1fff) || (c >= 0x2010 && c <= 0x2027) ||
           (c >= 0x2030 && c <= 0xd7ff) || (c >= 0xe000 && c <= 0xffef) ||
           (c >= 0x10000 && c <= 0x10ffff);
}

bool tree_sitter_smali_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
    if (valid_symbols[L]) {
        while (iswspace(lexer->lookahead)) {
            skip(lexer);
        }

        if (lexer->lookahead == 'L') {
            lexer->result_symbol = L;
            advance(lexer);
            return true;
        }
    }

    if (valid_symbols[CLASS_IDENTIFIER]) {
        lexer->result_symbol = CLASS_IDENTIFIER;

        // backtick-quoted simple name (API 30+), may contain spaces
        if (lexer->lookahead == '`') {
            advance(lexer);
            while (lexer->lookahead != '`' && lexer->lookahead != '\r' && lexer->lookahead != '\n' &&
                   !lexer->eof(lexer)) {
                advance(lexer);
            }
            if (lexer->lookahead != '`') {
                return false;
            }
            advance(lexer);
            return true;
        }

        // any simple name character, stop at /
        while (is_simple_name_char(lexer->lookahead)) {
            advance(lexer);
        }
        return true;
    }

    return false;
}
