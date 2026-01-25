{
  description = "QMK firmware development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            qmk
            python3
            uv

            # Additional development tools that are useful for QMK
            git
            gnumake
            gcc-arm-embedded
            avrdude
            dfu-util
            dfu-programmer
          ];

          shellHook = ''
            echo "QMK development environment loaded"
            echo "Available tools:"
            echo "  - qmk: $(qmk --version 2>/dev/null || echo 'QMK CLI')"
            echo "  - python: $(python --version)"
            echo "  - uv: $(uv --version)"
            echo ""
            echo "Run 'qmk setup' if this is your first time using QMK"
          '';
        };
      });
}
