CoDeSys+=  М          0         @        @   2.3.9.55К  Philip Henriksen @   ConfigExtensionb         CommConfigEx7             CommConfigExEnd   MEХ                  IB                    % QB                    %   ME_End   CM©      CM_End   CT≈   €€€€€€€€   CT_End   ME6               PFC200 CS 2ETH RS (FW03-...) IB                    % QB                    %   ME_End   CMJ     CM_End   CTf  €€€€€€€€   CT_End   P}         P_End   CTШ  €€€€€€€€   CT_End   Pѓ         P_End   CT   €€€€€€€€   CT_End   Pб         P_End   CTь  €€€€€€€€   CT_End   P         P_End   CT.  €€€€€€€€   CT_End   MEГ                 IB                    % QB                    %   ME_End   CMЧ     CM_End   CT≥  €€€€€€€€   CT_End   P          P_End   CTе  €€€€€€€€   CT_End   Pь         P_End   CT  €€€€€€€€   CT_End   P.         P_End   CTI  €€€€€€€€   CT_End   P`         P_End   CT{  €€€€€€€€   CT_End   PТ         P_End   CT≠  €€€€€€€€   CT_End   Pƒ         P_End   CTя  €€€€€€€€   CT_End   Pц         P_End   CT  €€€€€€€€   CT_End   P(         P_End   CTC  €€€€€€€€   CT_End   PZ         P_End   CTu  €€€€€€€€   CT_End   PМ         P_End   CTІ  €€€€€€€€   CT_End   PЊ         P_End   CTў  €€€€€€€€   CT_End   Pр         P_End   CT  €€€€€€€€   CT_End   P"         P_End   CT=  €€€€€€€€   CT_End   PT         P_End   CTo  €€€€€€€€   CT_End   PЖ         P_End   CT°  €€€€€€€€   CT_End   PЄ         P_End   CT”  €€€€€€€€   CT_End   ME(                 IB                    % QB                    %   ME_End   CM<     CM_End   CTX  €€€€€€€€   CT_End   ConfigExtensionEnd/    @                             ”l] 5   Libraries\ @      ЌЌЌЌЌЌЌЌ             хmq[        #   @   H   C:\POWERTECH\PROJECT\!UTVIKLING\BIBLIOTEKER\BACNET\LIBRARIES\TESTLIB.LIB          F_TESTFUNCTION               xInput            э€                 F_TestFunction                                      :ё]  А   €€€€           FB_TESTFUNCTIONBLOCK               xInVar            э€              rInVar            э€              wInVar           э€                 xOutVar            э€              rOutVar            э€	                       :ё]  А   €€€€    \   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\PFC200\STANDARD.LIB          ASCIIBYTE_TO_STRING               byt           э€                 ASCIIBYTE_TO_STRING                                         vдzS  А   €€€€           CONCAT               STR1               э€              STR2               э€                 CONCAT                                         vдzS  А   €€€€           CTD           M             э€           Variable for CD Edge Detection      CD            э€           Count Down on rising edge    LOAD            э€	           Load Start Value    PV           э€
           Start Value       Q            э€           Counter reached 0    CV           э€           Current Counter Value             vдzS  А   €€€€           CTU           M             э€            Variable for CU Edge Detection       CU            э€       
    Count Up    RESET            э€	           Reset Counter to 0    PV           э€
           Counter Limit       Q            э€           Counter reached the Limit    CV           э€           Current Counter Value             vдzS  А   €€€€           CTUD           MU             э€            Variable for CU Edge Detection    MD             э€            Variable for CD Edge Detection       CU            э€
       
    Count Up    CD            э€           Count Down    RESET            э€           Reset Counter to Null    LOAD            э€           Load Start Value    PV           э€           Start Value / Counter Limit       QU            э€           Counter reached Limit    QD            э€           Counter reached Null    CV           э€           Current Counter Value             vдzS  А   €€€€           DELETE               STR               э€              LEN           э€	              POS           э€
                 DELETE                                         vдzS  А   €€€€           F_TRIG           M             э€                 CLK            э€           Signal to detect       Q            э€	           Edge detected             vдzS  А   €€€€           FIND               STR1               э€	              STR2               э€
                 FIND                                     vдzS  А   €€€€           INSERT               STR1               э€	              STR2               э€
              POS           э€                 INSERT                                         vдzS  А   €€€€           LEFT               STR               э€              SIZE           э€                 LEFT                                         vдzS  А   €€€€           LEN               STR               э€                 LEN                                     vдzS  А   €€€€           MID               STR               э€              LEN           э€	              POS           э€
                 MID                                         vдzS  А   €€€€           R_TRIG           M             э€                 CLK            э€           Signal to detect       Q            э€	           Edge detected             vдzS  А   €€€€        
   REAL_STATE               RESET            э€           Reset the variable       ERROR           э€           Error detected             vдzS  А   €€€€           REPLACE               STR1               э€	              STR2               э€
              L           э€              P           э€                 REPLACE                                         vдzS  А   €€€€           RIGHT               STR               э€              SIZE           э€                 RIGHT                                         vдzS  А   €€€€           RS               SET            э€              RESET1            э€	                 Q1            э€                       vдzS  А   €€€€           RTC           M             э€              DiffTime            э€                 EN            э€              PDT           э€                 Q            э€              CDT           э€                       vдzS  А   €€€€           SEMA           X             э€                 CLAIM            э€
              RELEASE            э€                 BUSY            э€                       vдzS  А   €€€€           SR               SET1            э€              RESET            э€                 Q1            э€                       vдzS  А   €€€€           STANDARD_VERSION               EN            э€                 STANDARD_VERSION                                     vдzS  А   €€€€           STRING_COMPARE               STR1               э€              STR2               э€                 STRING_COMPARE                                      vдzS  А   €€€€           STRING_TO_ASCIIBYTE               str               э€                 STRING_TO_ASCIIBYTE                                     vдzS  А   €€€€           TOF           M             э€           internal variable 	   StartTime            э€           internal variable       IN            э€       ?    starts timer with falling edge, resets timer with rising edge    PT           э€           time to pass, before Q is set       Q            э€       2    is FALSE, PT seconds after IN had a falling edge    ET           э€           elapsed time             vдzS  А   €€€€           TON           M             э€           internal variable 	   StartTime            э€           internal variable       IN            э€       ?    starts timer with rising edge, resets timer with falling edge    PT           э€           time to pass, before Q is set       Q            э€       0    is TRUE, PT seconds after IN had a rising edge    ET           э€           elapsed time             vдzS  А   €€€€           TP        	   StartTime            э€           internal variable       IN            э€       !    Trigger for Start of the Signal    PT           э€       '    The length of the High-Signal in 10ms       Q            э€           The pulse    ET           э€       &    The current phase of the High-Signal             vдzS  А   €€€€    Z   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\PFC200\IECSFC.LIB          SFCACTIONCONTROL     
      S_FF                 RS    э€              L_TMR                    TON    э€              D_TMR                    TON    э€              P_TRIG                 R_TRIG    э€              SD_TMR                    TON    э€              SD_FF                 RS    э€              DS_FF                 RS    э€              DS_TMR                    TON    э€              SL_FF                 RS    э€              SL_TMR                    TON    э€           
      N            э€           Non stored action qualifier    R0            э€       #    Overriding reset action qualifier    S0            э€           Set (stored) action qualifier    L            э€	           Time limited action qualifier    D            э€
           Time delayed action qualifier    P            э€           Pulse action qualifier    SD            э€       *    Stored and time delayed action qualifier    DS            э€       %    Delayed and stored action qualifier    SL            э€       *    Stored and time limited action qualifier    T           э€           Current time       Q            э€       1    Associated action is executed, if Q equals TRUE             hюQ  А    €€€€                  PLC_PRG           Test                   Fb_TestFunctionBlock    3               BoolVar             3               RealVar             3               BoolOut             3               _ImpVar_51_6                                             ћl]  @   €€€€            
 н   э€€€3   ( |*      K   К*     K   Ш*     K   ¶*     K   ї*                 »*         +                     A±рСБъ”ђH ZJ≤            Tcp/Ip (Level 2 Route)  Test 3S Tcp/Ip Level 2 Router Driver    6   й  Address IP address or hostname 
   10.49.1.22    и  Port     Ч	   ь  TargetId         7   d   Motorola byteorder                No    Yes                 A±рСБъ”ђH ZJ≤            Tcp/Ip (Level 2 Route)  Test 3S Tcp/Ip Level 2 Router Driver    6   й  Address IP address or hostname 
   10.49.1.22    и  Port     Ч	   ь  TargetId         7   d   Motorola byteorder                No    Yes   K         @   ”fо\О\      , £  FП                     CoDeSys 1-2.2   а€€€  ЌЌЌЌЌЌЌЌ                     ∞.  r       л      
   т         у         ч          ш                    "          $                                                   '          (          ±          ≥          µ          є          Ї         ґ          ѕ          –          —         Љ          Њ          ј          ¬          ƒ         ∆      А           P  »          ћ         ќ       А  “                    ~          А          С          Т          У          Ф          Х          Ц          Ч          Ш          Щ          Б          В          Г          Д          Е          Ж          З       @  И       @  К       @  Л       @  М       @  П       @  Ґ         †         ®          Ю       А  M         N          O          P          `         a          t          y          z          b         c          X          d         e         _          Q          \         R          K          U         X         Z         в          д         ж      
   и         к         м         о         с         п          р          т         у      €€€€ф          х          ч      (                                                                        "         !          #          $         Ы          ^          f         g          h          i          j          k         F          H         J         L          N         P         R          U         S          T          V          W          §          •          l          o          p          q          r          s         u          ё          v         ¶          І      €€€€|         ~         А         x          z      (   ©          Ђ         %         ≠          Ѓ          ѓ         @         Ё          д          Ў         &          р          	                   ж          з          и         й          к         ™          ≤          і          ђ          ≠          ѓ          ∞          Ј          Є          Њ          м          н                            I         J         K          	          L         M          Щ                             ё          P         Q          S          )          	          	          Б           	          +	       @  ,	       @  -	      €€€€Z	      €€€€[	      €€€€ЌЌЌЌ        €€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€Ѓ.  т         у         ч          ш                    "          $                                                   '          (          ±          ≥          µ          є          Ї         ґ          ѕ          –          —         Љ          Њ          ј          ¬          ƒ         ∆      А           P  »          ћ         ќ       А  “          И         К       `  П      фЯ Ґ         ®          N         O         `         a          t          y          z          b          c          X          _         \         R          K          U         X         Z         в          д         ж      
   и         к         м         о         с         п          р          т         у      €€€€ф          х          ч      (   #         $          Ы          g          h         i          j          k         F          H         J         L          N         P         R          U         S          T          V          W          §          o          p          q          r          s         u          ё          v         ¶          w          І      €€€€|         ~         А         x          z      (   ©          Ђ          %         ≠          Ѓ          ѓ         @         Ё          а         б      X  д          Ў         &         `р          	                   ж          з          и         й          к         ™          ≤          і          ђ          ≠          ѓ          ∞          Ј          Є          Њ          м          н          ю          €                                       I         J         K          	          L         M          Щ                             ё          P         Q          S          )          	          	          Б           	          +	       @  ,	       @  -	      €€€€Z	         [	      €€€€ЌЌЌЌ        €€€€€€€€∞.  т         у         ч          ш                    "          $                                                   '          (          ±          ≥          µ          є          Ї         ґ          ѕ          –          —         Љ          Њ          ј          ¬          ƒ         ∆      А           P  »          ћ         ќ       А  “          И         К       `  П      фЯ Ґ         ®          N         O         `         a          t          y          z          b          c          X          _         \         R          K          U         X         Z         в          д         ж      
   и         к         м         о         с         п          р          т         у      €€€€ф          х          ч      (   #         $          Ы          g          h         i         j          k         F          H         J         L          N         P         R          U         S          T          V          W          §          o          p          q          r          s         u          ё          v         ¶          w          І      €€€€|         ~         А         x          z      (   ©          Ђ          %         ≠          Ѓ          ѓ         @         Ё          а         б      X  д          Ў         &         `р          	                   ж          з          и         й          к         ™          ≤          і          ђ          ≠          ѓ          ∞          Ј          Є          Њ          м          н          ю          €                                       I         J         K          	          L         M          Щ                             ё          P         Q          S          )          	          	          Б           	          +	       @  ,	       @  -	      €€€€Z	         [	      €€€€ЌЌЌЌ        €€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€ЌЌЌЌщ€€€  ЌЌЌЌЌЌЌЌ                                                   І  	   	   Name                 €€€€
   Index                 €€         SubIndex                 €          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Variable    	             €€€€
   Value                Variable       Min                Variable       Max                Variable          5  
   	   Name                 €€€€
   Index                 €€         SubIndex                 €          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write    	   Type          ~         INT   UINT   DINT   UDINT   LINT   ULINT   SINT   USINT   BYTE   WORD   DWORD   REAL   LREAL   STRING    
   Value                Type       Default                Type       Min                Type       Max                Type          5  
   	   Name                 €€€€
   Index                 €€         SubIndex                 €          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write    	   Type          ~         INT   UINT   DINT   UDINT   LINT   ULINT   SINT   USINT   BYTE   WORD   DWORD   REAL   LREAL   STRING    
   Value                Type       Default                Type       Min                Type       Max                Type          d        Member    	             €€€€   Index-Offset                 €€         SubIndex-Offset                 €          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Min                Member       Max                Member          Я  	   	   Name                 €€€€   Member    	             €€€€
   Value                Member    
   Index                 €€         SubIndex                 €          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Min                Member       Max                Member          І  	   	   Name                 €€€€
   Index                 €€         SubIndex                 €          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Variable    	             €€€€
   Value                Variable       Min                Variable       Max                Variable                         т€€€  ЌЌЌЌЌЌЌЌ               В   _Dummy@    @   @@    @   @             §п@             §п@@   @     Аv@@   ; @+   с€€€  ЌЌЌЌЌЌЌЌ                                  Аv@      4@   ∞             Аv@      D@   ∞                       ј       @                           Аf@      4@     Аf@                Аv@     Аf@     @u@     Аf@        чЅл           Module.Root-1__not_found__    PLC Configuration€€€€ IB          % QB          % MB          %   o     Module.K_Bus1Module.Root   Parameter.KbusBusMode	201019000Module.K_Bus11  DINTParameter.KbusCycleTime	201019001Module.K_Bus1000010000100050000DINTParameter.KbusThreadPriority	201019002Module.K_Bus00015DINT/Parameter.KbusSetOutputsToZeroOnApplicationStop	201019003Module.K_Bus11  BOOLK-Bus     IB          % QB          % MB          %    o     Module.PFC200MODBUS2Module.Root   Parameter.PlcStopBehaviour
2010330101Module.PFC200MODBUS11  BYTE Parameter.FiledbusErrorBehaviour
2010330102Module.PFC200MODBUS11  BYTEParameter.TcpOperation
2010330201Module.PFC200MODBUS11  BOOLParameter.TcpPort
2010330202Module.PFC200MODBUS502502165535UINTParameter.TcpTimeout
2010330203Module.PFC200MODBUS600600165535UDINTParameter.UdpOperation
2010330301Module.PFC200MODBUS11  BOOLParameter.UdpPort
2010330302Module.PFC200MODBUS502502165535UINTParameter.RtuOperation
2010330401Module.PFC200MODBUS00  BOOLParameter.NodeId
2010330402Module.PFC200MODBUS111247BYTEParameter.ResponseTimeout
2010330403Module.PFC200MODBUS10010013600000UDINTParameter.Interface
2010330404Module.PFC200MODBUS00  BYTEParameter.Baud
2010330405Module.PFC200MODBUS115200115200  UDINTParameter.StopBits
2010330406Module.PFC200MODBUS1112BYTEParameter.Parity
2010330407Module.PFC200MODBUS11  BYTEParameter.FlowCtrl
2010330408Module.PFC200MODBUS00  BYTEParameter.PhysInterface
2010330409Module.PFC200MODBUS00  BYTEModbus variables    IB          % QB          % MB          %    o     Module.MB_MASTER3Module.Root    Modbus-Master    IB          % QB          % MB          %    ”fо\	hм]     ЌЌЌЌЌЌЌЌ           VAR_GLOBAL
END_VAR
                                                                                  "   ,   §4             ”fо\                   start   Called when program starts    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     stop   Called when program stops    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     before_reset   Called before reset takes place    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     after_reset   Called after reset took place    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     shutdown#   Called before shutdown is performed    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     excpt_watchdog%   Software watchdog OF IEC-task expired    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     excpt_access_violation   Access violation    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     excpt_dividebyzero   Division BY zero    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     after_reading_inputs   Called after reading of inputs    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     before_writing_outputs    Called before writing of outputs    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.  
   debug_loop   Debug loop at breakpoint    k   FUNCTION systemevent: DWORD
VAR_INPUT
  dwEvent: DWORD;
  dwFilter: DWORD;
  dwOwner: DWORD;
END_VAR
    ∞.     online_change+   Is called after CodeInit() at Online-Change    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  !   ∞.     before_download$   Is called before the Download starts    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  "   ∞.  $ы€€€  ЌЌЌЌЌЌЌЌ               ЌЌЌЌЌЌЌЌ           Standard хmq[	хmq[      ЌЌЌЌЌЌЌЌ                         	як]     ЌЌЌЌЌЌЌЌ           VAR_CONFIG
END_VAR
                                                                                   '              , й  МП           Global_Variables ”fо\	”fо\     ЌЌЌЌЌЌЌЌ           VAR_GLOBAL
END_VAR
                                                                                               '           6  , F  йП           Var_Constant ”fо\	”fо\6    ЌЌЌЌЌЌЌЌ        L   VAR_GLOBAL CONSTANT
	BTFDevice:		STRING[15] := 'Device 4194302';
END_VAR
                                                                                               '           	   , FПй           Variable_Configuration ”fо\	”fо\	     ЌЌЌЌЌЌЌЌ           VAR_CONFIG
END_VAR
                                                                                                 А   |0|0 @v    @T   Courier @       HH':'mm':'ss @      dd'-'MM'-'yyyy   dd'-'MM'-'yyyy HH':'mm':'ss   Р                               .     €   €€€  ћ3 €€€   € €€€     
    @€А  €€€     @      DEFAULT             System      А   |0|0 @v    @T   Courier @       HH':'mm':'ss @      dd'-'MM'-'yyyy   dd'-'MM'-'yyyy HH':'mm':'ss   Р                      )   HH':'mm':'ss @                             dd'-'MM'-'yyyy @       '   <  , йПМ           typ_ReadProperty ”fо\	”fо\      ЌЌЌЌЌЌЌЌ        5   TYPE typ_ReadProperty :
STRUCT
END_STRUCT
END_TYPE              3   ,     О           PLC_PRG ”l]	ћl]      ЌЌЌЌЌЌЌЌ        u   PROGRAM PLC_PRG
VAR
	Test:			Fb_TestFunctionBlock;
	BoolVar:		BOOL;
	RealVar:		REAL;

	BoolOut:		BOOL;
END_VAR)    €€€€               TRUE        €€€€   	   !          Test    Fb_TestFunctionBlockМ                                                               €€€€"      &         BoolVar1             €€€€"      &         RealVar1            €€€€               BoolVar1        €€€€      $                F_TestFunctionb                                           €€€€%      )         BoolOut1          d                    э€€€,   П£         "   TestLib.lib 13.6.19 08:25:14 @Jм]#   Standard.lib 20.5.14 08:13:26 @ЖтzS!   Iecsfc.lib 30.1.13 13:05:12 @hюQ   )   F_TestFunction @      eTest                  Fb_TestFunctionBlock @             Global_Variables @          !   ASCIIBYTE_TO_STRING @                  CONCAT @        	   CTD @        	   CTU @        
   CTUD @           DELETE @           F_TRIG @        
   FIND @           INSERT @        
   LEFT @        	   LEN @        	   MID @           R_TRIG @           REAL_STATE @          REPLACE @           RIGHT @           RS @        	   RTC @        
   SEMA @           SR @           STANDARD_VERSION @          STRING_COMPARE @          STRING_TO_ASCIIBYTE @       	   TOF @        	   TON @           TP @              Global Variables 0 @           F   SFCActionControl @      SFCActionType       SFCStepType                      Globale_Variablen @                          ЌЌЌЌЌЌЌЌ           2 у  у           €€€€€€€€€€€€€€€€  
             ъ€€€, £ПF        ш€€€, 4 4 К®                      POUs                PLC_PRG  3   €€€€           
   Data types                typ_ReadProperty  <  €€€€             Visualizations  €€€€              Global Variables                 Global_Variables                     Var_Constant  6                  Variable_Configuration  	   €€€€                                         ЌЌЌЌЌЌЌЌ             чmq[∞.             Ѓ.      ∞.                	   localhost            P      	   localhost            P      	   localhost            P     Ќ;Ё\    їТm