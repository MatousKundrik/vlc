/*******************************************************************************
 * video_output.h : video output thread
 * (c)1999 VideoLAN
 *******************************************************************************
 * This module describes the programming interface for video output threads.
 * It includes functions allowing to open a new thread, send pictures to a
 * thread, and destroy a previously oppenned video output thread.
 *******************************************************************************
 * Requires:
 *  "config.h"
 *  "common.h"
 *  "mtime.h"
 *  "vlc_thread.h"
 *  "video.h"
 *******************************************************************************/

/*******************************************************************************
 * vout_thread_t: video output thread descriptor
 *******************************************************************************
 * Any independant video output device, such as an X11 window, is represented
 * by a video output thread, and described using following structure.
 *******************************************************************************/
typedef struct vout_thread_s
{
    /* Thread properties and locks */
    boolean_t           b_die;                                   /* `die' flag */
    boolean_t           b_error;                               /* `error' flag */
    boolean_t           b_active;                             /* `active' flag */
    pthread_t           thread_id;                 /* id for pthread functions */
    pthread_mutex_t     lock;                                   /* thread lock */
    int *               pi_status;                    /* temporary status flag */

    /* Common display properties */
    int                 i_width;                /* current output method width */
    int                 i_height;              /* current output method height */
    int                 i_screen_depth;                      /* bits per pixel */
    int                 i_bytes_per_pixel;                /* real screen depth */
    float               f_x_ratio;                 /* horizontal display ratio */
    float               f_y_ratio;                   /* vertical display ratio */

    /* Output method */
    p_vout_sys_t        p_sys;                         /* system output method */

    /* Video heap */
    int                 i_pictures;                       /* current heap size */
    picture_t           p_picture[VOUT_MAX_PICTURES];              /* pictures */

#ifdef STATS    
    /* Statistics */
    count_t         c_loops;                               /* number of loops */
    count_t         c_idle_loops;                     /* number of idle loops */
    count_t         c_pictures;           /* number of pictures added to heap */
#endif

    /* Rendering functions - these functions are of vout_render_blank_t and 
     * vout_render_line_t, but are not declared here using these types since
     * they require vout_thread_t to be defined */
/*    void (* RenderRGBBlank)         ( struct vout_thread_s *p_vout, pixel_t pixel,
                                      int i_x, int i_y, int i_width, int i_height );
    void (* RenderPixelBlank)       ( struct vout_thread_s *p_vout, pixel_t pixel,
                                      int i_x, int i_y, int i_width, int i_height );
    void (* RenderRGBLine)          ( struct vout_thread_s *p_vout, picture_t *p_pic,
                                      int i_x, int i_y, int i_pic_x, int i_pic_y, 
                                      int i_width, int i_line_width, int i_ratio ); 
    void (* RenderPixelLine)        ( struct vout_thread_s *p_vout, picture_t *p_pic,
                                      int i_x, int i_y, int i_pic_x, int i_pic_y, 
                                      int i_width, int i_line_width, int i_ratio ); 
    void (* RenderRGBMaskLine)      ( struct vout_thread_s *p_vout, picture_t *p_pic,
                                      int i_x, int i_y, int i_pic_x, int i_pic_y, 
                                      int i_width, int i_line_width, int i_ratio ); 
    void (* RenderPixelMaskLine)    ( struct vout_thread_s *p_vout, picture_t *p_pic,
                                      int i_x, int i_y, int i_pic_x, int i_pic_y, 
                                      int i_width, int i_line_width, int i_ratio ); 
  */  /* ?? add YUV types */
} vout_thread_t;

/*******************************************************************************
 * Prototypes
 *******************************************************************************/
vout_thread_t * vout_CreateThread               ( 
#if defined(VIDEO_X11)
                                                  Display *p_display, Window root_window, 
#elif defined(VIDEO_FB)
                                                  //??void
#endif
                                                  int i_width, int i_height, int *pi_status
                                                );

void            vout_DestroyThread              ( vout_thread_t *p_vout, int *pi_status );

picture_t *     vout_CreatePicture              ( vout_thread_t *p_vout, int i_type, 
						  int i_width, int i_height, int i_bytes_per_line );
void            vout_DestroyPicture             ( vout_thread_t *p_vout, picture_t *p_pic );
void            vout_DisplayPicture             ( vout_thread_t *p_vout, picture_t *p_pic );
void            vout_LinkPicture                ( vout_thread_t *p_vout, picture_t *p_pic );
void            vout_UnlinkPicture              ( vout_thread_t *p_vout, picture_t *p_pic );

#ifdef DEBUG
void            vout_PrintHeap                  ( vout_thread_t *p_vout, char *psz_str );
#endif
















