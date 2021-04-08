# Overview

This is just a quick template to start a standalone ESP-IDF project. It uses the hello-world example as a template. It contains the following components:

- C++ as the application language
- Sample wrapper interface for abstracting the RTOS function call (for unit testing)
- Linting (cpplint)
- Formatting (clang-format with Google style)
- Tests (Google Test and Google Mock)
- Rough documentation (Doxygen-style comments for developer reference)
- CI/CD (Github Actions)

CI/CD performs the following things:

- uses one of espressif's published docker images
- checks that the application builds successfully
- checks that the linter/formatter script passes
- builds, runs, and checks that all unit tests pass
