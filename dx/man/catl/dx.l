


     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



     NNNNAAAAMMMMEEEE
          dx - start the Data Explorer visualization system.
          Optionally directly start the User Interface (_d_x_u_i), the
          executive (_d_x_e_x_e_c), the Data Prompter, the Module Builder or
          the Tutorial.

     SSSSYYYYNNNNOOOOPPPPSSSSIIIISSSS
          dx   [ -8bitcmap < private | shared | 0-1 > ]
               [ -builder ]
               [ -cache < on | off > ]
               [ -colors < colors file > ]
               [ -connect < host:port > ]
               [ -data < path list > ]
               [ -directory  < dir > ]
               [ -display < display name > ]
               [ -dxroot < dir > ]
               [ -echo ]
               [ -edit ]
               [ -encode ]
               [ -exec < executable > ]
               [ -execonly ]
               [ -execute ]
               [ -execute_on_change ]
               [ -full ]
               [ -file < filename > ]
               [ -help ]
               [ -highlight < on | off > ]
               [ -host < host name > ]
               [ -hwrender < gl | opengl > ]
               [ -image ]
               [ -include < path list > ]
               [ -key < 64bit hex > ]
               [ -license < type > ]
               [ -local ]
               [ -log < on | off > ]
               [ -macros  < path list > ]
               [ -mdf < filename > ]
               [ -memory < # of Mbytes > ]
               [ -menubar ]
               [ -metric ]
               [ -modules < path list > ]
               [ -morehelp ]
               [ -nodeid ]
               [ -optimize < memory | precision > ]
               [ -outboarddebug ]
               [ -processors ]
               [ -program < filename > ]
               [ -prompter ]
               [ -readahead < on | off > ]
               [ -script [ < script file > ] ]
               [ -startup ]
               [ -suppress ]



     Page 1                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               [ -timing < on | off >]
               [ -trace < on | off > ]
               [ -trialkey ]
               [ -tutor ]
               [ -uionly | -execonly ]
               [ -verbose ]
               [ -version]

          dx   -prompter      ( start the Data Prompter )
               [ -full ]
               [ -file ] [ < header file name > ]

          dx   -builder  ( start the Module Builder )
               [-file ] [ < .mb file name > ]







     DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
          _d_x is the command that starts the Data Explorer Startup
          Window, and optionally starts the _D_a_t_a _E_x_p_l_o_r_e_r _U_s_e_r
          _I_n_t_e_r_f_a_c_e, _D_a_t_a _E_x_p_l_o_r_e_r _E_x_e_c_u_t_i_v_e, _D_a_t_a _E_x_p_l_o_r_e_r _D_a_t_a
          _P_r_o_m_p_t_e_r, _D_a_t_a _E_x_p_l_o_r_e_r _M_o_d_u_l_e _B_u_i_l_d_e_r or the _D_a_t_a _E_x_p_l_o_r_e_r
          _T_u_t_o_r_i_a_l.

          The Data Explorer Startup Window is an X windows/Motif based
          application which allows easy access to the other
          subsystemes of the Data Explorer visualization system.

          The _D_a_t_a _E_x_p_l_o_r_e_r _U_s_e_r _I_n_t_e_r_f_a_c_e is an X windows/Motif based
          application that provides a visual programming environment
          and an interface to the executive.  The executive provides
          the computational tools and mechanisms to create data
          visualizations. The

          _D_a_t_a _E_x_p_l_o_r_e_r _D_a_t_a _P_r_o_m_p_t_e_r is an X windows/Motif based
          application that helps users import data in a variety of
          formats, and provides general purpose visual programs to
          visual imported data, leading to a shortened "time to first
          picture".

          The _D_a_t_a _E_x_p_l_o_r_e_r _M_o_d_u_l_e _B_u_i_l_d_e_r is an X windows/Motif based
          application that helps users build their own modules to be
          included in a custom version of Data Explorer.

          The _D_a_t_a _E_x_p_l_o_r_e_r _T_u_t_o_r_i_a_l is an application that helps
          users learn to use Data Explorer by leading them through a
          sequence of tasks.  Users can easily skip around in the
          tutorial in order to concentrate on tasks of most use to



     Page 2                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



          their work.

          For a more complete description of the _D_a_t_a _E_x_p_l_o_r_e_r _U_s_e_r
          _I_n_t_e_r_f_a_c_e _a_n_d _E_x_e_c_u_t_i_v_e see the IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa
          EEEExxxxpppplllloooorrrreeeerrrr UUUUsssseeeerrrr''''ssss GGGGuuuuiiiiddddeeee.  For a more complete description of
          the _D_a_t_a _E_x_p_l_o_r_e_r _D_a_t_a _P_r_o_m_p_t_e_r see the IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn
          DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr QQQQuuuuiiiicccckkkkSSSSttttaaaarrrrtttt GGGGuuuuiiiiddddeeee.  For a more thorough
          description of the _D_a_t_a _E_x_p_l_o_r_e_r _M_o_d_u_l_e _B_u_i_l_d_e_r see the IIIIBBBBMMMM
          VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr PPPPrrrrooooggggrrrraaaammmmmmmmeeeerrrr''''ssss RRRReeeeffffeeeerrrreeeennnncccceeee.

     OOOOPPPPTTTTIIIIOOOONNNNSSSS
          With no options the _d_x command starts the Startup Window, an
          X windows/Motif program from which the other parts of the
          Data Explorer system can be started.  The various command
          line options and environment variables listed below can be
          specified to change the default behavior.

          Options set by including them in the DXARGS environment
          variable are placed at the start of the command line,
          followed by any options set by environment variables,
          followed by explicit command line arguments.  When
          conflicting options are given, the last option has
          precedence.

          ----8888bbbbiiiittttccccmmmmaaaapppp < private | shared | 0-1  | -1 >
               Overrides the DX8BITCMAP environment variable (see
               ENVIRONMENT VARIABLES below).

          ----ccccaaaacccchhhheeee < on | off >
               Turn on or off the executive caching system. When the
               Data Explorer caching mechanism is enabled the Data
               Explorer executive automatically caches the
               intermediate results generated during its visualization
               computations.  Unlike standard caching mechanisms,
               these results are accessed by means of their functional
               derivation.  This allows for automatic graph
               optimization and helps to avoid the recomputation of
               previously utilized intermediates, especially when the
               Data Explorer sequencer is being used.  In certain rare
               instances, a machine with a small amount of memory may
               want to disable this caching to conserve memory and
               reduce paging.  Default = on.

          ----ccccoooolllloooorrrrssss < colors file >
               Override DXCOLORS environment variable (see ENVIRONMENT
               VARIABLES below).

          ----ccccoooonnnnnnnneeeecccctttt < host:port >
               Start a distributed executive only (no user interface).

          ----ddddaaaattttaaaa < path list >
               Override DXDATA environment variable (see ENVIRONMENT



     Page 3                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               VARIABLES below).

          ----ddddiiiirrrreeeeccccttttoooorrrryyyy < dir >
               Cause the executive to be run in the given directory.

          ----ddddiiiissssppppllllaaaayyyy < display name >
               Set the name of the X display to be used by the user
               interface and the executive.

          ----ddddxxxxrrrrooooooootttt < dir >
               Overrides the default dx root directory.

          ----eeeecccchhhhoooo < dir >
               Echo the command lines without executing them.

          ----eeeeddddiiiitttt
               Cause the user interface to be started with the Visual
               Program Editor (VPE) window as the top level window of
               the user interface (the top level window is denoted by
               an anchor in the upper left hand corner). Also see
               -image, -startup,  and -menubar.

          ----eeeennnnccccooooddddeeee < filename >
               Encode the given file into a binary format with a key
               (which must be specified with the -key option). For
               example
                   dx -encode -key 1234567890abcdef foo.net The
               resulting file can only be encoded by the DX user
               interface when the same key is used. For example
                   dx -image -key 1234567890abcdef foo-e.net

          ----eeeexxxxeeeecccc < executive executable >
               Use the given file as a replacement for the executive.
               This option allows a user to build and use his/her own
               custom executive.

          ----eeeexxxxeeeeccccoooonnnnllllyyyy
               Start the executive in remote mode in which it will
               then await a connection from the user interface.  The
               user interface is not started with this option. Also
               see -script.

          ----eeeexxxxeeeeccccuuuutttteeee
               Execute once after the user interface has made a
               connection with the executive.

          ----eeeexxxxeeeeccccuuuutttteeee____oooonnnn____cccchhhhaaaannnnggggeeee
               Cause Data Explorer to go into execute-on-change mode
               at start up.  Execute-on-change mode causes the Visual
               Program to be executed any time any of the values (i.e.
               module inupts, interactor values...)  in the program
               change.



     Page 4                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



          ----ffffiiiilllleeee < filename >
               Start the Data Prompter, Module Builder, or Data
               Explorer User Interface with the header file filename.

          ----ffffuuuullllllll
               When used with -prompter, starts the full Data
               Prompter.

          ----hhhheeeellllpppp
               Print a brief listing of options and usage for _d_x.

          ----hhhhiiiigggghhhhlllliiiigggghhhhtttt < on | off >
               Turn on or off module execution highlighting. If
               highlighting is turned on, the user interface will
               highlight each module as it is executed.  Default = on.

          ----hhhhoooosssstttt < host name >
               Override DXHOST environment variable (see ENVIRONMENT
               VARIABLES below).

          ----hhhhwwwwrrrreeeennnnddddeeeerrrr < gl | opengl >
               Override the default hardware rendering choice on
               platforms where both are supported. Default is opengl.
               Sets the DXHWMOD environment variable to either
               DXhwdd.o or DXhwddOGL.o.

          ----iiiimmmmaaaaggggeeee
               Cause the user interface to be started with the image
               window as the top level window of the user interface.
               Also, control panels that are configured to open
               automatically are opened.  Also see -edit, -startup and
               -menubar.

          ----iiiinnnncccclllluuuuddddeeee < path list >
               Override DXINCLUDE environment variable (see
               ENVIRONMENT VARIABLES below).

          ----kkkkeeeeyyyy < 64bit hex >
               16 character hexidecimal (64bit) number that is used to
               encode and decode .net files. See -encode.

          ----lllliiiicccceeeennnnsssseeee < type >
               Force a specific license for either the user interface
               or executive.  The following are valid values for type:

               runtime: forces a run-time license (UI or executive).

               timed: forces a timed (limited function) license (UI
               only).

               develop: forces a developer license (UI or executive).




     Page 5                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



          ----llllooooccccaaaallll
               Override the DXHOST environment variable (if set) and
               cause the executive to be run on the local host.  In
               the absence of the DXHOST environment variable, this is
               the default.

          ----lllloooogggg < on | off >
               Turn on or off executive logging. If logging is on then
               the executive logs output to the file _d_x._l_o_g in the
               directory where the executive is executing.  Default =
               off.

          ----mmmmaaaaccccrrrroooossss < path list >
               Override the DXMACROS environment variable (see
               ENVIRONMENT VARIABLES below).

          ----mmmmeeeennnnuuuubbbbaaaarrrr
               Start Data Explorer with a menubar as the anchor
               window.  Also, control panels that are configured to
               open automatically are opened.  See also -image, -edit,
               and -startup.

          ----mmmmddddffff < mdf file >
               Override the DXMDF environment variable (see
               ENVIRONMENT VARIABLES below).

          ----mmmmeeeemmmmoooorrrryyyy < # of MB >
               Set the maximum amount of memory, in megabytes rounded
               up to a two megabyte boundary, that the executive is
               able to allocate. Default = the amount of physical
               memory minus 8 MB.

          ----mmmmeeeettttrrrriiiicccc
               Have the ui use metric units when possible, for example
               for setting the image size for printing postscript
               images.

          ----mmmmoooodddduuuulllleeeessss < pathlist >
               Set the list of directories to be searched for outboard
               modules.

          ----mmmmoooorrrreeeehhhheeeellllpppp
               Displays this information

          ----nnnnooooddddeeeeiiiidddd
               print out the node id of the machine that the command
               is run on. The node id is used when generating a
               license.

          ----ooooppppttttiiiimmmmiiiizzzzeeee < memory | precision >
               Select whether to minimize memory usage or produce more
               color-accurate images.  When memory is optimized, image



     Page 6                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               objects are generated with 24 bits/pixel instead of 96,
               and ReadImage will produce delayed color images if
               supported by the format. The default is precision.

          ----oooouuuuttttbbbbooooaaaarrrrddddddddeeeebbbbuuuugggg
               Enable user to start outboard modules manually for
               debugging when they are called in a visual program.

          ----pppprrrroooocccceeeessssssssoooorrrrssss
               For Data Explorer SMP, sets the number of processors to
               use.

          ----pppprrrrooooggggrrrraaaammmm < programname >
               Start the user interface with the visual program
               filename.

          ----pppprrrroooommmmpppptttteeeerrrr
               Start the data prompter.

          ----rrrreeeeaaaaddddaaaahhhheeeeaaaadddd < on | off >
               Specify whether or not the executive reads ahead in its
               input stream before executing the commands it receives
               from the stream.  If this is turned off, then the
               executive will execute each command line as it is
               received.  This is useful for certain debugging
               purposes, such as memory leak detection.  Default = on.

          ----ssssccccrrrriiiipppptttt [ < script file > ]
               Run just the executive in script mode. If a file name
               is provided then the executive reads and executes
               commands from the given script and then terminates.  If
               a file is not provided then when the executive starts
               up it enters _i_n_t_e_r_a_c_t_i_v_e mode where it waits for script
               commands.  Also see -execonly.

          ----ssssttttaaaarrrrttttuuuupppp
               Start Data Explorer with the startup window as the
               initial window. This is the default. See also -image,
               -edit, and -menubar.

          ----ssssuuuupppppppprrrreeeessssssss
               Do not open any control panels at start-up. This is
               used in -image mode and -menubar mode only.

          ----ttttiiiimmmmeeeedddd
               Start DX using a timed license.

          ----ttttiiiimmmmiiiinnnngggg < on | off >
               Turn on or off the executive timing mechanism. If
               enabled, then when the executive exits it will list on
               standard output or the logging file timing statistics
               for each module that was used during the course of



     Page 7                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               execution.  Default = off.

          ----ttttrrrraaaacccceeee < on | off >
               Turn on or off the executive trace mechanism. When
               tracing is enabled the executive displays informative
               messages about the execution sequence on either
               standard output or the log file if logging is enabled.
               Default = off.

          ----ttttrrrriiiiaaaallllkkkkeeeeyyyy
               Determines the information necessary for generating a
               trialkey.

          ----ttttuuuuttttoooorrrr
               Start the Data Explorer tutorial.

          ----uuuuiiiioooonnnnllllyyyy
               Cause the user interface to be started without making a
               connection to an executive.

          ----vvvveeeerrrrbbbboooosssseeee
               Echo commands in the _d_x script as they are executed.

          ----vvvveeeerrrrssssiiiioooonnnn
               Print version numbers of various executables.

     EEEENNNNVVVVIIIIRRRROOOONNNNMMMMEEEENNNNTTTT VVVVAAAARRRRIIIIAAAABBBBLLLLEEEESSSS
          The following environment variables provide an alternate way
          to set certain of the command line options, or alter the
          default behavior of Data Explorer in some way. Options set
          with environment variables are overridden if the same option
          is also specified on the command line.  Options set with
          DXARGS are overridden by both environment variables and
          explicit command line options.

          DDDDXXXX8888BBBBIIIITTTTCCCCMMMMAAAAPPPP
               When Data Explorer displays images in 8-bit windows, it
               makes every effort to create an accurate representation
               of the image using the default colormap shared among
               applications using 8-bit windows.  If the colors
               required by Data Explorer are not present in the
               colormap and there are not enough free color cells
               available in the shared color map for their allocation,
               Data Explorer will find approximations among the colors
               that are available.  However, in certain circumstances,
               the difference between the desired color and the
               approximation is found to be too great to be
               acceptable.  In such circumstances, DX will allocate a
               private colormap for more accurate results.  In this
               case, depending on your X server, you may need to move
               the mouse to select the Image or Display window in
               order for the correct colors to appear.  The -8bitcmap



     Page 8                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               flag sets the level at which the change to using a
               private colormap is made.  The value of this parameter
               should be a number between 0 and 1, or "private" or
               "shared", and it repressents the Euclidean distance in
               RGB color space, normalized to 1, for the maximum
               allowed discrepancy.  If you set this parameter to 1,
               then a private colormap will never be used. If you set
               it to -1, then a private colormap will always be used.
               The default is 0.1.

          DDDDXXXXAAAARRRRGGGGSSSS
               This contains the default set of arguments used by the
               _d_x script. The arguments are prepended to those given
               to _d_x on the command line.  This variable allows for
               the _d_x command to be easily customized.

          DDDDXXXXAAAAXXXXEEEESSSSMMMMAAAAXXXXWWWWIIIIDDDDTTTTHHHH
               Sets the number of digits in axes tick labels at which
               a switch to scientific notation is made. The default is
               7.

          DDDDXXXXCCCCOOOOLLLLOOOORRRRSSSS
               This contains the name of an alternate  file that
               contains mappings of color names to red, green, blue
               triplets in a format like that of the default color
               file found in /usr/lpp/dx/lib/colors.txt.

          DDDDXXXXDDDDAAAATTTTAAAA
               This contains a colon separated list of directories in
               which the executive will search for data files.  Also
               see the -data option.

          DDDDXXXXDDDDEEEEFFFFAAAAUUUULLLLTTTTIIIIMMMMAAAAGGGGEEEEFFFFOOOORRRRMMMMAAAATTTT
               Sets the image type to either 24-bit color images or
               floating-point-based 96 bit images.  This affects the
               behavior of Render and ReadImage.  This variable can be
               set to either DXByte (24 bits) or DXFloat (96 bits).

          DDDDXXXXDDDDEEEELLLLAAAAYYYYEEEEDDDDCCCCOOOOLLLLOOOORRRRSSSS
               If set to anything other than 0, enables ReadImage to
               create delayed color images if the image is a tiff
               format image saved in a byte-with-colormap format or a
               gif image.

          DDDDXXXXEEEEXXXXEEEECCCC
               Specifies an executive to be run at start-up.

          DDDDXXXXFFFFLLLLIIIINNNNGGGG
               If DXFLING is set to 1, then for hardware-rendered
               images, in rotation mode and execute-on-change mode, if
               you drag the mouse across the image, and release the
               mouse button outside the image, the object in the image



     Page 9                                         (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               will begin to rotate, and will continue to rotate until
               you click inside the image.  The direction and speed of
               the mouse motion before release will affect the
               rotation direction and rotation speed of the object in
               the window.

          DDDDXXXXGGGGAAAAMMMMMMMMAAAA
               Sets the gamma correction for software-rendered images
               displayed to the screen using the Display and Image
               tools.  The default value is 2, except for 8-bit
               windows on the sgi architecture.

          DDDDXXXXGGGGAAAAMMMMMMMMAAAA____8888BBBBIIIITTTT,,,,
               DDDDXXXXGGGGAAAAMMMMMMMMAAAA____11112222BBBBIIIITTTT,,,, DDDDXXXXGGGGAAAAMMMMMMMMAAAA____22224444BBBBIIIITTTT sets the gamma correction
               factor for software-rendered images for the windows
               with the indicated window depth.  Overrides the value
               set by DXGAMMA.

          DDDDXXXXHHHHOOOOSSSSTTTT
               This contains the name of the host machine that will
               run the executive. If this is not set then a default of
               "localhost" is used, unless the local host is a PVS
               console in which case the default is to run the
               executive on the PVS.  Also see the -host, -local and
               -server options.

          DDDDXXXXHHHHWWWWGGGGAAAAMMMMMMMMAAAA
               Sets the gamma correction for hardware-rendered images
               displayed to the screen using the Display and Image
               tools.  The default value is 2.

          DDDDXXXXHHHHWWWWMMMMOOOODDDD
               Specifies the name of the hardware rendering library to
               use when more than one is supported. Should be either
               DXhwdd.o or DXhwddOGL.o.

          DDDDXXXXIIIINNNNCCCCLLLLUUUUDDDDEEEE
               This contains a colon separated list of directories in
               which the executive will search for "included" scripts.
               Also see the -include option.

          DDDDXXXXMMMMAAAACCCCRRRROOOOSSSS
               This contains a colon separated list of directories in
               which the user interface searches for macros that will
               be automatically loaded.  When running in script mode
               one must "include" all the macros by hand prior to
               referencing them.  Also see the -macros option.

          DDDDXXXXMMMMDDDDFFFF
               This contains the name of a module description file
               (mdf) that contains user defined modules for a
               customized version of the executive.  Also see the -mdf



     Page 10                                        (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               option.

          DDDDXXXXMMMMEEEEMMMMOOOORRRRYYYY
               sets the amount of memory (in megabytes) that can be
               used by the executive.

          DDDDXXXXMMMMOOOODDDDUUUULLLLEEEESSSS
               This contains a colon separated list of directories in
               which the executive searches for outboard modules. Also
               see the -modules option.

          DDDDXXXX____NNNNEEEESSSSTTTTEEEEDDDD____LLLLOOOOOOOOPPPPSSSS
               For faces, loops, and edges data, if set, allows loops
               other than the enclosing loop for a face to be listed
               first. However, there is a consequent decrease in
               performance if this environment variable is set.

          DDDDXXXXNNNNOOOO____BBBBAAAACCCCKKKKIIIINNNNGGGG____SSSSTTTTOOOORRRREEEE
               If set to anything, disables framebuffer readbacks.
               Setting this environment variable may improve
               performance of interaction with hardware rendered
               images, especially for machines for which readback is
               slow. The default behavior is that framebuffer
               readbacks are enabled. If you set this environment
               variable, not that some interactions using the Image
               tool will result in a black image while interaction is
               taking place. However, if you are not using the Image
               tool, it is strongly recommended that you set this
               environment variable.

          DDDDXXXXPPPPIIIIXXXXEEEELLLLTTTTYYYYPPPPEEEE
               sets the image type to either 24-bit color images or
               floating-point-based 96-bit images (the default). This
               affects the behavior of Render and ReadImage.  This
               variable can be set to either DXByte (24 bits) or
               DXFloat (96 bits).  Setting this variable to DXByte
               will result in images taking up less memory.

          DDDDXXXXPPPPRRRROOOOCCCCEEEESSSSSSSSOOOORRRRSSSS
               Sets the number of processors to be used for Data
               Explorer SMP.

          DDDDXXXXRRRROOOOOOOOTTTT
               Specifies the top-level directory for all the files and
               directories needed by Data Explorer.

          DDDDXXXXSSSSHHHHMMMMEEEEMMMM
               If set to anything other than -1, forces shared memory
               to be used (if allowed by the architecture).  If set to
               -1, (if allowed by the architecture) will cause the
               data segment to simply be extended. Please see Appendix
               C of the Data Explorer User Guide for more information.



     Page 11                                        (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



          DDDDXXXXTTTTRRRRIIIIAAAALLLLKKKKEEEEYYYY
               Can be used in place of the expiration file
               ($DXROOT/expiration) for a trial license.  The value of
               the variable is the string specifying the trial key.
               Takes precedence over both $DXROOT/expiration and
               DXTRIALKEYFILE.

          DDDDXXXXTTTTRRRRIIIIAAAALLLLKKKKEEEEYYYYFFFFIIIILLLLEEEE
               Specifies the name of the expiration file for a trial
               license.  Takes precedence over $DXROOT/expiration.

          DDDDXXXX____UUUUSSSSEEEERRRR____IIIINNNNTTTTEEEERRRRAAAACCCCTTTTOOOORRRR____FFFFIIIILLLLEEEE
               Specifies a file containing user interactors for use by
               the SuperviseState and SuperviseWindow modules.

     EEEEXXXXAAAAMMMMPPPPLLLLEEEESSSS
          The next few examples assume that none of the DX environment
          variables have been set.

          1. To start both the user interface and the executive with
          the network named _c_f_d._n_e_t:
               dx -edit -program cfd


          2. To start and execute the visual program _c_f_d._n_e_t in image
          mode with /usr/users/me and /usr/data as data directories:
               dx -image -execute -data '/usr/users/me:/usr/data' cfd

          3. To run just the executive on the script named _f_1_5_w_i_n_g:

               dx -script -file f15wing

          4. To start the user interface and execute the user
          customized executive named _m_y_d_x_e_x_e_c containing user defined
          modules described in _c_u_s_t_o_m._m_d_f:

               dx -edit -mdf custom.mdf -exec mydxexec

          5. To start the Data Prompter :

               dx -prompter

          6. To start the Module Builder :

               dx -builder
          7. To start the Tutorial :

               dx -tutorial


     SSSSEEEEEEEE AAAALLLLSSSSOOOO
          README* - The README file(s) found in the dx



     Page 12                                        (printed 12/22/98)






     DDDDXXXX((((1111VVVV))))           IIIIBBBBMMMM VVVViiiissssuuuuaaaalllliiiizzzzaaaattttiiiioooonnnn DDDDaaaattttaaaa EEEExxxxpppplllloooorrrreeeerrrr           DDDDXXXX((((1111VVVV))))



               installation directory are an added source of
               information.  html/allguide.htm contains html versions
               of the documentation.




















































     Page 13                                        (printed 12/22/98)



