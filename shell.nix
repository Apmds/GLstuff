{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    gnumake
    pkg-config
    
    # OpenGL and GLFW dependencies (X11 + Wayland)
    libGL
    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
    
    # Wayland specific (for Sway/Wayland support)
    wayland
    wayland-protocols
    libxkbcommon
  ];

  shellHook = ''
    export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.lib.makeLibraryPath (with pkgs; [
      libGL
      xorg.libX11
      xorg.libXrandr
      xorg.libXinerama
      xorg.libXcursor
      xorg.libXi
      wayland
      libxkbcommon
    ])}"
  '';
}
