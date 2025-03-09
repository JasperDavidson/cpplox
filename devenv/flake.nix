{
  description = "C++ Development";

  inputs = {
    nixpkgs.url = "github:Patryk27/nixpkgs/improve-clang-tools";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
        let
          pkgs = import nixpkgs { inherit system; };
          llvm = pkgs.llvmPackages_latest;
          lib = nixpkgs.lib;

        in
          {
            devShell = pkgs.mkShell {
              nativeBuildInputs = [
                pkgs.cmake
                llvm.lldb

                pkgs.clang-tools
                llvm.clang # clangd

                pkgs.gtest
              ];

              buildInputs = [
                # stdlib for cpp
                llvm.libcxx
              ];

              # CXXFLAGS = "-std=c++17";
              CPATH = builtins.concatStringsSep ":" [
                (lib.makeSearchPathOutput "dev" "include" [ llvm.libcxx ])
                (lib.makeSearchPath "resource-root/include" [ llvm.clang ])
              ];
            };
          }
    );
}
