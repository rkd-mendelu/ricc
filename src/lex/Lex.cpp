#include "Lex.hpp"

namespace TPJparser {

    Lex::Lex(std::istream& stream) : _stream(stream) {
        _currentState = START;
    }

    std::map<std::string,Token::tokenType> Lex::keywordMap = {
            {"EOF", Token::KW_EOF},
            {"int", Token::KW_INT},
            {"bool", Token::KW_BOOL},
            {"float", Token::KW_FLOAT},
            {"void", Token::KW_VOID},
            {"string", Token::KW_STRING},
            {"if", Token::KW_IF},
            {"else", Token::KW_ELSE},
            {"return", Token::KW_RETURN},
            {"switch", Token::KW_SWITCH},
            {"case", Token::KW_CASE},
            {"default", Token::KW_DEFAULT},
            {"break", Token::KW_BREAK},
            {"continue", Token::KW_CONTINUE},
            {"class", Token::KW_CLASS},
            {"private", Token::KW_PRIVATE},
            {"protected", Token::KW_PROTECTED},
            {"public", Token::KW_PUBLIC},
            {"struct", Token::KW_STRUCT},
            {"cout", Token::KW_COUT},
            {"true", Token::KW_TRUE},
            {"false", Token::KW_FALSE},
            {"while", Token::KW_WHILE},
    };

    void Lex::setCurrentState(lexState currentState) {
        this->_currentState = currentState;
    }

    void Lex::ungetToken(Token& t) {
        _tokenStack.push(t);
    }

    Lex::lexState Lex::getCurrentState() {
        return this->_currentState;
    }

    void Lex::clearLexState() {
        this->_currentState = START;
    }

    void keywordCheck(Token& token) {
        if(Lex::keywordMap.find(token.getText()) != Lex::keywordMap.end()) {
            token.setTokenType(Lex::keywordMap.at(token.getText()));
        } else {
            token.setTokenType(Token::IDENTIFIER);
        }
    }

    Token& Lex::getTokenFromFile() {
        TPJparser::Token& token = this->_tokenPool.getItem();
        char c;

        while(_stream.get(c)) {
            switch (getCurrentState()) {
                case START:
                    if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == '_') { // Identifiers starting with a-Z, A-Z or _
                        token.addChar(c);
                        setCurrentState(IDENTIFIER);
                    } else if (c > 47 && c < 58) { // Numbers 0-9
                        token.addChar(c);
                        setCurrentState(INTEGER);
                    } else if (c == EOF) {
                        clearLexState();
                        token.setTokenType(Token::EOF_CHAR);
                        return token;
                    } else {
                        switch (c) {
                            case '<':
                                setCurrentState(LESS);
                                break;
                            case '=':
                                setCurrentState(ASSIGNMENT);
                                break;
                            case '/':
                                setCurrentState(DIV);
                                break;
                            case '!':
                                setCurrentState(EXCL_MARK);
                                break;
                            case '"':
                                setCurrentState(STRING_DOUBLE_QUOTES_START);
                                break;
                            case '\'':
                                setCurrentState(STRING_SINGLE_QUOTES_START);
                                break;
                            case '&':
                                setCurrentState(AND_FIRST_MARK);
                                break;
                            case '|':
                                setCurrentState(OR_FIRST_MARK);
                                break;
                            case '-':
                                setCurrentState(MINUS_SIGN);
                                break;
                            // ONE CHAR TOKENS
                            case '*':
                                clearLexState();
                                token.setTokenType(Token::MULTI);
                                return token;
                            case '+':
                                clearLexState();
                                token.setTokenType(Token::PLUS);
                                return token;
                            case '>':
                                clearLexState();
                                token.setTokenType(Token::LARGE);
                                return token;
                            case '(':
                                clearLexState();
                                token.setTokenType(Token::BRACKET_ROUND_OPEN);
                                return token;
                            case ')':
                                clearLexState();
                                token.setTokenType(Token::BRACKET_ROUND_CLOSE);
                                return token;
                            case '[':
                                clearLexState();
                                token.setTokenType(Token::BRACKET_SQUARE_OPEN);
                                return token;
                            case ']':
                                clearLexState();
                                token.setTokenType(Token::BRACKET_SQUARE_CLOSE);
                                return token;
                            case '{':
                                clearLexState();
                                token.setTokenType(Token::BRACKET_CURLY_OPEN);
                                return token;
                            case '}':
                                clearLexState();
                                token.setTokenType(Token::BRACKET_CURLY_CLOSE);
                                return token;
                            case ';':
                                clearLexState();
                                token.setTokenType(Token::SEMICOLON);
                                return token;
                            case ',':
                                clearLexState();
                                token.setTokenType(Token::COMMA);
                                return token;
                            case '.':
                                clearLexState();
                                token.setTokenType(Token::DOT);
                                return token;
                            default:
                                if(!std::isspace(c)) {
                                    token.setTokenType(Token::ERROR_TOKEN);
                                    clearLexState();
                                    return token;
                                }
                                break;
                        }
                    }
                    break;
                case IDENTIFIER:
                    if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58) || c == '_') { // letter, numbers plus _ sign
                        token.addChar(c);
                    } else {
                        _stream.putback(c);
                        clearLexState();

                        keywordCheck(token);
                        return token;
                    }
                    break;
                case INTEGER:
                    if (c > 47 && c < 58) {
                        token.addChar(c);
                    } else if (c == '.') {
                        token.addChar(c);
                        setCurrentState(FLOAT);
                    } else {
                        _stream.putback(c);
                        clearLexState();

                        token.setTokenType(Token::INTEGER);
                        return token;
                    }
                    break;
                case FLOAT:
                    if (c > 47 && c < 58) {
                        token.addChar(c);
                    } else {
                        _stream.putback(c);
                        clearLexState();

                        token.setTokenType(Token::FLOAT);
                        return token;
                    }
                    break;
                case LESS:
                    clearLexState();
                    if(c == '<') {
                        token.setTokenType(Token::OUTPUT);
                        return token;
                    } else {
                        _stream.putback(c);
                        token.setTokenType(Token::LESS);
                        return token;
                    }
                case ASSIGNMENT:
                    clearLexState();
                    if(c == '=') {
                        token.setTokenType(Token::EQUAL);
                        return token;
                    } else {
                        _stream.putback(c);
                        token.setTokenType(Token::ASSIGNMENT);
                        return token;
                    }
                case DIV:
                    if(c == '/') {
                        setCurrentState(COMMENT_LINE);
                    } else if (c == '*') {
                        setCurrentState(COMMENT_BLOCK_START);
                    } else {
                        _stream.putback(c);
                        clearLexState();

                        token.setTokenType(Token::DIV);
                        return token;
                    }
                    break;
                case EXCL_MARK:
                    clearLexState();
                    if(c == '=') {
                        token.setTokenType(Token::NOT_EQUAL);
                        return token;
                    } else {
                        _stream.putback(c);
                        token.setTokenType(Token::EXCLAMATION);
                        return token;
                    }
                case COMMENT_LINE:
                    if(c == '\n') {
                        clearLexState();
                    }
                    break;
                case COMMENT_BLOCK_START:
                    if(c == '*') {
                        setCurrentState(COMMENT_BLOCK_STAR);
                    }
                    break;
                case COMMENT_BLOCK_STAR:
                    if(c == '/') {
                        clearLexState();
                    } else if (c != '*') {
                        setCurrentState(COMMENT_BLOCK_START);
                    }
                    break;
                case STRING_DOUBLE_QUOTES_START:
                    token.setTokenType(Token::STRING);
                    if(c == '"') {
                        clearLexState();
                        return token;
                    } else {
                        token.addChar(c);
                        setCurrentState(STRING_DOUBLE_QUOTES_BODY);
                    }
                    break;
                case STRING_DOUBLE_QUOTES_BODY:
                    if(c == '"') {
                        clearLexState();
                        return token;
                    } else if (c == EOF || c == '\n') {
                        clearLexState();

                        token.setTokenType(Token::ERROR_TOKEN);
                        return token;
                    } else {
                        token.addChar(c);
                    }
                    break;
                case STRING_SINGLE_QUOTES_START:
                    token.setTokenType(Token::STRING);
                    if(c == '\'') {
                        clearLexState();
                        return token;
                    } else {
                        setCurrentState(STRING_SINGLE_QUOTES_BODY);
                        token.addChar(c);
                    }
                    break;
                case STRING_SINGLE_QUOTES_BODY:
                    if(c == '\'') {
                        clearLexState();
                        return token;
                    } else if (c == EOF) {
                        clearLexState();

                        token.setTokenType(Token::ERROR_TOKEN);
                        return token;
                    } else {
                        token.addChar(c);
                    }
                    break;
                case AND_FIRST_MARK:
                    clearLexState();

                    if(c == '&') {
                        token.setTokenType(Token::AND);
                    } else {
                        token.setTokenType(Token::ERROR_TOKEN);
                    }

                    return token;
                case OR_FIRST_MARK:
                    clearLexState();

                    if(c == '|') {
                        token.setTokenType(Token::OR);
                    } else {
                        token.setTokenType(Token::ERROR_TOKEN);
                    }

                    return token;
                case MINUS_SIGN:
                    clearLexState();
                    if(c == '>') {
                        token.setTokenType(Token::POINTER);
                    } else {
                        _stream.putback(c);
                        token.setTokenType(Token::MINUS);
                    }

                    return token;
            }
        }
        token.setTokenType(Token::END_TOKEN);
        return token;
    }

    Token& Lex::getTokenFromStack() {
        return _tokenStack.top();
    }

    Token& Lex::getToken() {
        return _tokenStack.empty() ? getTokenFromFile() : getTokenFromStack();
    }
}
