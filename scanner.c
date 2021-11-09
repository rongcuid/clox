#include "scanner.h"

#include <stdio.h>
#include <string.h>

#include "common.h"

struct scanner {
  const char *start;
  const char *current;
  int line;
};

struct scanner scanner;

static bool is_at_end() { return *scanner.current == '\0'; }

static struct token make_token(enum token_type type) {
  struct token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  return token;
}

static struct token error_token(const char *message) {
  struct token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = strlen(message);
  token.line = scanner.line;
  return token;
}

static char advance() { return *scanner.current++; }

static char peek() { return *scanner.current; }

static char peek_next() {
  if (is_at_end())
    return '\0';
  return scanner.current[1];
}

static bool match(char expected) {
  if (is_at_end())
    return false;
  if (*scanner.current != expected)
    return false;
  ++scanner.current;
  return true;
}

static void skip_whitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '\n':
      scanner.line++;
      advance();
      break;
    case '/':
      if (peek_next() == '/') {
        while (peek() != '\n' && !is_at_end())
          advance();
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

static struct token string() {
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n')
      scanner.line++;
    advance();
  }

  if (is_at_end())
    return error_token("Unterminated string.");

  advance();
  return make_token(TOKEN_STRING);
}

static bool is_digit(char c) { return c >= '0' && c <= '9'; }

static struct token number() {
  while (is_digit(peek()))
    advance();
  if (peek() == '.' && is_digit(peek_next())) {
    advance();
    while (is_digit(peek()))
      advance();
  }
  return make_token(TOKEN_NUMBER);
}

static bool is_alpha(char c) {
  return (c >= 'a' && c <= 'z')
    || (c >= 'A' && c <= 'Z')
    || c == '_';
}

static enum token_type identifier_type() {
  return TOKEN_IDENTIFIER;
}

static struct token identifier() {
  while (is_alpha(peek()) || is_digit(peek())) advance();
  return make_token(identifier_type());
}

//////

void init_scanner(const char *source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}

struct token scan_token() {
  skip_whitespace();
  scanner.start = scanner.current;

  if (is_at_end())
    return make_token(TOKEN_EOF);

  char c = advance();
  if (is_alpha(c)) 
    return identifier();
  if (is_digit(c))
    return number();

  switch (c) {
  case '(':
    return make_token(TOKEN_LEFT_PAREN);
  case ')':
    return make_token(TOKEN_RIGHT_PAREN);
  case '{':
    return make_token(TOKEN_LEFT_BRACE);
  case '}':
    return make_token(TOKEN_RIGHT_BRACE);
  case ';':
    return make_token(TOKEN_SEMICOLON);
  case ',':
    return make_token(TOKEN_COMMA);
  case '.':
    return make_token(TOKEN_DOT);
  case '-':
    return make_token(TOKEN_MINUS);
  case '+':
    return make_token(TOKEN_PLUS);
  case '/':
    return make_token(TOKEN_SLASH);
  case '*':
    return make_token(TOKEN_STAR);
  case '!':
    return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
  case '=':
    return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
  case '<':
    return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  case '"':
    return string();
  }

  return error_token("Unexpected character.");
}