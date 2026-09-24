# Why was the project configuration designed this way?

The main idea is to support separate compilation of both projects without having to compile both of their dependencies.

The projects are split into 2 folders containing only the required files for self sufficient compilation. Current structure also supports shared dependencies that facilitate central management of the project basically turning it into monorepo.