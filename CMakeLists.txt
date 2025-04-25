SET(SOURCES ui_SplashScreen.c
    ui_MainScreen.c
    ui_PropertiesScreen.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_img_903157970.c
    ui_img_leftarrow_png.c
    ui_img_uparrow_png.c
    ui_img_rightarrow_png.c
    ui_img_downarrow_png.c
    ui_img_101005223.c)

add_library(ui ${SOURCES})
