static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
};

/* enable or disable (1 means enable, 0 disable) bell sound when password is incorrect */
static const int xbell = 0;

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* time */
static const float textsize        = 32.0;
static const float text_x          = 16.0;
static const float text_y          = 16.0;
static const char* textfamily      = "serif";
static const double textcolorred   = 255;
static const double textcolorblue  = 255;
static const double textcolorgreen = 255;

/* Background image */
static const char* lockscreen_path = "WALLPAPER_PATH"; // env variable that slock is going to look for
static const int image_mode = 1;  // 1 to fill, 0 to fit
static const int blur_radius = 8; // Define blur radius
