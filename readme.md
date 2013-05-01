## DCC (DCPU C Compiler)

## Front End

### Description

The front end reads source files, builds the AST and then generates intermediate code.
The front end is separated to two phases: First the AST is built from the source code (scanning and parsing) and preprocessed at the same time. After the AST has been built semantic analysis is run on the AST while generating the intermediate representation.

### 1. AST Generation

- **Parser** (`front/parser`)
 - Parses the tokens (Recursive descent)
 - Owns a **Tokenizer**
- **Tokenizer** (`front/token`)
 - Removes whitespace token
 - Parses number tokens
 - Owns a **Preprocessor**
- **Preprocessor** (`pre/preprocessor`)
 - Applies macro replacement
 - Applies file inclusion
 - Owns a stack of **Scanners** (for file inclusion)
- **Scanner** (`pre/scanner`)
 - Creates preprocessing tokens from the characters
 - Adds every word to external `StringMap`
 - Owns a **CharMapper**
- **CharMapper** (`pre/char_mapper`)
 - Replaces trigraphs
 - Splices newlines
 - Owns a **FileReader**
- **FileReader** (`io/file_reader`)
 - Reads files character by character
 - Manages `SourceRange` iterators

### 2. Code Generation

TODO