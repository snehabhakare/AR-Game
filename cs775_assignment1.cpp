#include "cs775_assigment1.hpp"

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
    init(argc, argv);
    argSetDispFunc( mainLoop, 1 );
	argSetKeyFunc( keyFunc );
	count = 0;
    fps[0] = '\0';
	arUtilTimerReset();
    begin = clock();
    argMainLoop();
	return (0);
}

static void keyFunc( unsigned char key, int x, int y )
{
    int   value;

    switch (key) {
		case 0x1b:
            end = clock();
            elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            printf("Time elapsed: %f\n", elapsed_secs);
			cleanup();
			exit(0);
			break;
		case '1':
		case '-':
        	arGetLabelingThresh( arHandle, &value );
        	value -= 5;
        	if( value < 0 ) value = 0;
        	arSetLabelingThresh( arHandle, value );
        	// ARLOG("thresh = %d\n", value);
        	break;
		case '2':
		case '+':
        	arGetLabelingThresh( arHandle, &value );
       		value += 5;
        	if( value > 255 ) value = 255;
        	arSetLabelingThresh( arHandle, value );
        	// ARLOG("thresh = %d\n", value);
        	break;
		case 'd':
		case 'D':
        	arGetDebugMode( arHandle, &value );
       		value = 1 - value;
        	arSetDebugMode( arHandle, value );
            break;
        case 'h':
        case 'H':
            if( flipMode & AR_GL_FLIP_H ) flipMode = flipMode & AR_GL_FLIP_V;
            else                         flipMode = flipMode | AR_GL_FLIP_H;
            argViewportSetFlipMode( vp, flipMode );
            break;
        case 'v':
        case 'V':
            if( flipMode & AR_GL_FLIP_V ) flipMode = flipMode & AR_GL_FLIP_H;
            else                         flipMode = flipMode | AR_GL_FLIP_V;
            argViewportSetFlipMode( vp, flipMode );
        	break;
        case ' ':
            distF = 1 - distF;
            if( distF ) {
                argViewportSetDistortionMode( vp, AR_GL_DISTORTION_COMPENSATE_ENABLE );
            } else {
                argViewportSetDistortionMode( vp, AR_GL_DISTORTION_COMPENSATE_DISABLE );
            }
            break;
        case 'c':
            contF = 1 - contF;
            break;
		case '?':
		case '/':
			ARLOG("Keys:\n");
			ARLOG(" [esc]         Quit demo.\n");
			ARLOG(" - and +       Adjust threshhold.\n");
			ARLOG(" d             Activate / deactivate debug mode.\n");
			ARLOG(" h and v       Toggle horizontal / vertical flip mode.\n");
            ARLOG(" [space]       Toggle distortion compensation.\n");
			ARLOG(" ? or /        Show this help.\n");
			ARLOG("\nAdditionally, the ARVideo library supplied the following help text:\n");
			arVideoDispOption();
			break;
        case 'r':
            begin=clock();
            ball.body->SetTransform(init_pos,ball.body->GetAngle());
            reached=false;
            curr_player++;
            break;
		default:
			break;
	}
}

static void mainLoop(void)
{
    static int      contF2 = 0;
    static ARdouble patt_trans[3][4];
    static ARUint8 *dataPtr = NULL;
    ARMarkerInfo   *markerInfo;
    int             markerNum;
    ARdouble        err;
    int             imageProcMode;
    int             debugMode;
    int             j, k;

    /* grab a video frame */
    if( (dataPtr = (ARUint8 *)arVideoGetImage()) == NULL ) {
        arUtilSleep(2);
        return;
    }

    argDrawMode2D(vp);
    // arGetDebugMode( arHandle, &debugMode );
    if( debugMode == 0 ) {
        argDrawImage( dataPtr );
    }
    else {
        arGetImageProcMode(arHandle, &imageProcMode);
        if( imageProcMode == AR_IMAGE_PROC_FRAME_IMAGE ) {
            argDrawImage( arHandle->labelInfo.bwImage );
        }
        else {
            argDrawImageHalf( arHandle->labelInfo.bwImage );
        }
    }

    /* detect the markers in the video frame */
    if( arDetectMarker(arHandle, dataPtr) < 0 ) {
        cleanup();
        exit(0);
    }

    if( count % 60 == 0 ) {
        // sprintf(fps, "%f[fps]", 60.0/arUtilTimer());
        arUtilTimerReset();
    }
    count++;
    // glColor3f(0.0f, 1.0f, 0.0f);
    argDrawStringsByIdealPos(fps, 10, ysize-30);
    char* p;
    if(!reached){
        const char* x=std::to_string(double(clock()-begin)/CLOCKS_PER_SEC).c_str();
        int l=0;
        for(int l=0;x[l]!='\0';l++);
        p=(char*)malloc(l*sizeof(char));
        int m=0;
        for(;x[m]!='\0';m++)
        {
            p[m]=x[m];
        }
        p[m]='\0';
    }
    argDrawStringsByIdealPos(p, 10, ysize-60);
    
    markerNum = arGetMarkerNum( arHandle );
    if( markerNum == 0 ) {
        argSwapBuffers();
        return;
    }

    /* check for object visibility */
    markerInfo =  arGetMarker( arHandle ); 
    k = -1;
    for( j = 0; j < markerNum; j++ ) {
        // ARLOG("ID=%d, CF = %f\n", markerInfo[j].id, markerInfo[j].cf);
        if( patt_id == markerInfo[j].id ) {
            if( k == -1 ) {
                if (markerInfo[j].cf >= 0.7) k = j;
            } else if( markerInfo[j].cf > markerInfo[k].cf ) k = j;
        }
    }
    if( k == -1 ) {
        contF2 = 0;
        argSwapBuffers();
        return;
    }

    if( contF && contF2 ) {
        err = arGetTransMatSquareCont(ar3DHandle, &(markerInfo[k]), patt_trans, patt_width, patt_trans);
    }
    else {
        err = arGetTransMatSquare(ar3DHandle, &(markerInfo[k]), patt_width, patt_trans);
    }
    // sprintf(errValue, "err = %f", err);
    // glColor3f(0.0f, 1.0f, 0.0f);
    
    argDrawStringsByIdealPos(fps, 10, ysize-30);
    // char* p;
    if(!reached){
        const char* x=std::to_string(double(clock()-begin)/CLOCKS_PER_SEC).c_str();
        int l=0;
        for(int l=0;x[l]!='\0';l++);
        p=(char*)malloc(l*sizeof(char));
        int m=0;
        for(;x[m]!='\0';m++)
        {
            p[m]=x[m];
        }
        p[m]='\0';
    }
    argDrawStringsByIdealPos(p, 10, ysize-60);
    //ARLOG("err = %f\n", err);

    contF2 = 1;

    draw(patt_trans);

    argSwapBuffers();
}

static void   init(int argc, char *argv[])
{
    ARParam         cparam;
    ARGViewport     viewport;
    char            vconf[512];
    AR_PIXEL_FORMAT pixFormat;
    ARUint32        id0, id1;
    int             i;
    if( argc == 1 ) vconf[0] = '\0';
    else {
        strcpy( vconf, argv[1] );
        for( i = 2; i < argc; i++ ) {strcat(vconf, " "); strcat(vconf,argv[i]);}
    }

    
    printf("Please Enter the Number of Players: ");
    std::cin>>num_of_players;

    for (int i=0;i<num_of_players;i++)
        scores.push_back(big_score);
    printf("PLEASE ENTER YOUR LEVEL (0(beginner)-1(advanced)):  ");
    std::cin>>level;
    if(level!=0&& level !=1){
        printf("PLEASE ENTER VALID ENTRY \n ");
        printf("Setting default for now\n");
    }
    if(level==1){
        printf("Setting Advanced\n");
    
        x_range=b2Vec2(4*L/10,5*L/10);
        y_range=b2Vec2(0,B/8);
    }
    maze();

    /* open the video path */

	// ARLOGi("Using video configuration '%s'.\n", vconf);
    if( arVideoOpen( vconf ) < 0 ) exit(0);
    if( arVideoGetSize(&xsize, &ysize) < 0 ) exit(0);
    // ARLOGi("Image size (x,y) = (%d,%d)\n", xsize, ysize);
    if( (pixFormat=arVideoGetPixelFormat()) < 0 ) exit(0);
    if( arVideoGetId( &id0, &id1 ) == 0 ) {
        // ARLOGi("Camera ID = (%08x, %08x)\n", id1, id0);
        // sprintf(vconf, VPARA_NAME, id1, id0);
        if( arVideoLoadParam(vconf) < 0 ) {
            // ARLOGe("No camera setting data!!\n");
        }
    }

    /* set the initial camera parameters */
    if( arParamLoad(CPARA_NAME, 1, &cparam) < 0 ) {
        // ARLOGe("Camera parameter load error !!\n");
        exit(0);
    }
    arParamChangeSize( &cparam, xsize, ysize, &cparam );
    // ARLOG("*** Camera Parameter ***\n");
    arParamDisp( &cparam );
    if ((gCparamLT = arParamLTCreate(&cparam, AR_PARAM_LT_DEFAULT_OFFSET)) == NULL) {
        ARLOGe("Error: arParamLTCreate.\n");
        exit(-1);
    }
    
    if( (arHandle=arCreateHandle(gCparamLT)) == NULL ) {
        ARLOGe("Error: arCreateHandle.\n");
        exit(0);
    }
    if( arSetPixelFormat(arHandle, pixFormat) < 0 ) {
        ARLOGe("Error: arSetPixelFormat.\n");
        exit(0);
    }

    if( (ar3DHandle=ar3DCreateHandle(&cparam)) == NULL ) {
        ARLOGe("Error: ar3DCreateHandle.\n");
        exit(0);
    }

    if( (arPattHandle=arPattCreateHandle()) == NULL ) {
        ARLOGe("Error: arPattCreateHandle.\n");
        exit(0);
    }
    if( (patt_id=arPattLoad(arPattHandle, PATT_NAME)) < 0 ) {
        ARLOGe("pattern load error !!\n");
        exit(0);
    }
    arPattAttach( arHandle, arPattHandle );

    /* open the graphics window */
/*
    int winSizeX, winSizeY;
    argCreateFullWindow();
    argGetScreenSize( &winSizeX, &winSizeY );
    viewport.sx = 0;
    viewport.sy = 0;
    viewport.xsize = winSizeX;
    viewport.ysize = winSizeY;
*/
    viewport.sx = 0;
    viewport.sy = 0;
    viewport.xsize = xsize;
    viewport.ysize = ysize;
    if( (vp=argCreateViewport(&viewport)) == NULL ) exit(0);
    argViewportSetCparam( vp, &cparam );
    argViewportSetPixFormat( vp, pixFormat );
    //argViewportSetDispMethod( vp, AR_GL_DISP_METHOD_GL_DRAW_PIXELS );
    argViewportSetDistortionMode( vp, AR_GL_DISTORTION_COMPENSATE_DISABLE );

	if (arVideoCapStart() != 0) {
        ARLOGe("video capture start error !!\n");
        exit(0);
	}
    // scanf("Please Enter the Number of Players:  %d\n",num_of_players);
    
    
    
}

/* cleanup function called when program exits */
static void cleanup(void)
{
    arVideoCapStop();
    argCleanup();
	arPattDetach(arHandle);
	arPattDeleteHandle(arPattHandle);
	ar3DDeleteHandle(&ar3DHandle);
	arDeleteHandle(arHandle);
    arParamLTFree(&gCparamLT);
    arVideoClose();
}

static void get_angles(ARdouble* gl_para,float A[3]){
    A[0]=asin(-gl_para[2]);
    A[1]=atan2(gl_para[6],gl_para[10]);
    A[2]=atan2(gl_para[1],gl_para[0]);
    
}
static void draw( ARdouble trans[3][4] )
{
    ARdouble  gl_para[16];
    GLfloat   mat_diffuse[]     = {0.0f, 0.0f, 1.0f, 0.0f};
    GLfloat   mat_flash[]       = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat   mat_flash_shiny[] = {50.0f};
    GLfloat   light_position[]  = {100.0f,-200.0f,200.0f,0.0f};
    GLfloat   light_ambi[]      = {0.1f, 0.1f, 0.1f, 0.0f};
    GLfloat   light_color[]     = {1.0f, 1.0f, 1.0f, 0.0f};
    
    argDrawMode3D(vp);
    glClearDepth( 1.0 );
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    /* load the camera transformation matrix */
    argConvGlpara(trans, gl_para);
    float A[3];
    get_angles(gl_para,A);
    // printf("y angle is %f\n",A[0]*180/M_PI);
    // printf("x angle is %f\n",A[1]*180/M_PI);
    // printf("z angle is %f\n",A[2]*180/M_PI);
    float g_x=A[2]*180/M_PI;
    float g_y=A[0]*180/M_PI;
    world->SetGravity(b2Vec2(-gravity_constant*(g_x-90),gravity_constant*(g_y+15)));
    // printf("gravity is (%f,%f)\n",world->GetGravity().x,world->GetGravity().y);
    // printf("Pos is (%f,%f)\n",ball.body->GetPosition().x,ball.body->GetPosition().x);

    glMatrixMode(GL_MODELVIEW);
#ifdef ARDOUBLE_IS_FLOAT
    glLoadMatrixf( gl_para );
#else
    glLoadMatrixd( gl_para );
#endif

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambi);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_flash);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_flash_shiny);	
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_diffuse);

#if 1
    glRotatef(90,0,0,1);
    glColor3f(0.0f, 1.0f, 0.0f);

    for (int i=0;i<maze_list.size();i++)
        maze_list[i]->draw();
    glColor3f(1.0f, 1.0f, 0.0f);

    ball.draw();
    world->Step(frame_rate,5,5);
    ball.update();
    if(!reached){
        if(ball.body->GetPosition().x>x_range.x&&ball.body->GetPosition().x<x_range.y){
            if(ball.body->GetPosition().y>y_range.x&&ball.body->GetPosition().y<y_range.y)
            {
                end=clock();
                elapsed_secs=double(end-begin)/CLOCKS_PER_SEC;
                printf("Time Taken by Player %d = %f\n",curr_player,elapsed_secs);
                reached=true;
                scores[curr_player-1]=elapsed_secs;
                if(curr_player==num_of_players){
                    printf("Game Ends ...........!!!!!!!!!\n");
                    int min_index=1;
                    double min_time=scores[0];
                    for(int i=0;i<scores.size();i++){
                        if(scores[i]<min_time){
                            min_index=i+1;
                            min_time=scores[i];
                        }
                    }
                    printf("The Winner is Player %d with time %f\n",min_index,min_time);
                    cleanup();
			        exit(0);
                }
            }  
        }
    }

#else
    glTranslatef( 0.0f, 0.0f, 20.0f );
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidTeapot(40.0);
#endif
    glDisable(GL_LIGHT0);
    glDisable( GL_LIGHTING );

    glDisable( GL_DEPTH_TEST );
}
