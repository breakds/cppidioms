let pkgs = import <nixpkgs> {};

in pkgs.mkShell rec {
  name = "x11";
  
  buildInputs = with pkgs; [
    pkgconfig
    spdlog
    xorg.libX11
  ];
  
  shellHook = ''
    export PS1="$(echo -e '\u2600') {\[$(tput sgr0)\]\[\033[38;5;228m\]\w\[$(tput sgr0)\]\[\033[38;5;15m\]} (${name}) \\$ \[$(tput sgr0)\]"
    export CC=clang
    export CXX=clang++
  '';
}
