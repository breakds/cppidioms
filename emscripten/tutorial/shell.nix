let pkgs = import <nixpkgs> {};

    nodejs-current = pkgs.nodejs-12_x;

in pkgs.mkShell rec {
  name = "emcc";
  
  buildInputs = with pkgs; [
    nodejs-current
    (yarn.override { nodejs = nodejs-current; })
    autoconf
    automake
    emscripten

    # C++ Dependencies
    pkgconfig
    boost167
  ];
  shellHook = ''
    export PS1="\[$(tput sgr0)\]\[\033[38;5;150m\]$(echo -e '\uf3d3')\[$(tput sgr0)\]\[\033[38;5;15m\] {\[$(tput sgr0)\]\[\033[38;5;228m\]\w\[$(tput sgr0)\]\[\033[38;5;15m\]} \\$ \[$(tput sgr0)\]"
  '';
}
