static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#003355",   /* during input */
	[FAILED] = "#550000",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* enable or disable (1 means enable, 0 disable) bell sound when password is incorrect */
static const int xbell = 0;

/* Background image path, should be available to the user above */
/* env variable that slock is going to look for */
static const char* lockscreen_path = "LOCKSCREEN_PATH";
