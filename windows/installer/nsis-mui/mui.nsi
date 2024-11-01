!include MUI2.nsh

!insertmacro MUI_LANGUAGE "English"

; If you are using solid compression, files that are required before the actual 
; installation should be stored first in the data block, because this will make 
; your installer start faster. Include reserve file commands for such files 
; before your sections and functions:
ReserveFile /plugin MyPlugin.dll
!insertmacro MUI_RESERVEFILE_LANGDLL ;Language selection dialog

; *** Defined below ***
; !define MUI_COMPONENTSPAGE_SMALLDESC ;No value
; !define MUI_UI "myUI.exe" ;Value
; !define MUI_INSTFILESPAGE_COLORS "FFFFFF 000000" ;Two colors

; ===========
; Page header
; ===========

; The icon for the installer.
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"

; The icon for the uninstaller.
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; ===============
; MUI_HEADERIMAGE
; ===============
; Display an image on the header of the page.

; Bitmap image to display on the header of installers pages (recommended size: 
; 150x57 pixels).
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\nsis.bmp"

; FitControl : 
;     Stretch the image to fit the image control.
;
; NoStretchNoCropNoAlign : 
;     Do not stretch the image to fit the size of the image control. You should 
;     not use this option if you have a full size bitmap that fits exactly 
;     because the size of the field will be different if the user has a custom 
;     DPI setting or if the installer is using a CJK language.
;
; NoStretchNoCrop :
;     This is similar to NoStretchNoCropNoAlign but will align the image to the 
;     right edge when using a RTL language or if MUI_HEADERIMAGE_RIGHT is 
;     defined.
;
; AspectFitHeight :
;     Scale the image up or down until it is the same height as the image 
;     control while maintaining the image aspect ratio.
!define MUI_HEADERIMAGE_BITMAP_STRETCH "FitControl"

; Bitmap image to display on the header of installers pages when using a RTL 
; language (recommended size: 150x57 pixels).
!define MUI_HEADERIMAGE_BITMAP_RTL "${NSISDIR}\Contrib\Graphics\Header\nsis.bmp" 

; See MUI_HEADERIMAGE_BITMAP_STRETCH for a list of the available stretch modes.
!define MUI_HEADERIMAGE_BITMAP_RTL_STRETCH "FitControl"

; Bitmap image to display on the header of uninstaller pages (recommended size: 
; 150x57 pixels).
!define MUI_HEADERIMAGE_UNBITMAP "${NSISDIR}\Contrib\Graphics\Header\nsis.bmp"

; See MUI_HEADERIMAGE_BITMAP_STRETCH for a list of the available stretch modes.
!define MUI_HEADERIMAGE_UNBITMAP_STRETCH "FitControl"

; Bitmap image to display on the header of uninstallers pages when using a RTL 
; language (recommended size: 150x57 pixels).
!define MUI_HEADERIMAGE_UNBITMAP_RTL "${NSISDIR}\Contrib\Graphics\Header\nsis.bmp"

; See MUI_HEADERIMAGE_BITMAP_STRETCH for a list of the available stretch modes.
!define MUI_HEADERIMAGE_UNBITMAP_RTL_STRETCH "FitControl"

; Display the header image on the right side instead of the left side (when 
; using a RTL language it will be displayed on the left side instead of the 
; right side).
!define MUI_HEADERIMAGE_RIGHT

; Background color for the header, the Welcome page and the Finish page.
!define MUI_BGCOLOR FFFFFF

; Set a transparent background for the header's label controls. Useful for 
; custom user interfaces that set a bigger header image.
!define MUI_HEADER_TRANSPARENT_TEXT

; Text color for the header, the Welcome page and the Finish page.
!define MUI_TEXTCOLOR 000000

; ===================
; Interface resources
; ===================

; The interface file with the dialog resources. Change this if you have made 
; your own customized UI.
!define MUI_UI "${NSISDIR}\Contrib\UIs\modern.exe"

; The interface files with the dialog resource IDD_INST that contains a bitmap 
; control and space for the header bitmap.
!define MUI_UI_HEADERIMAGE "${NSISDIR}\Contrib\UIs\modern_headerbmp.exe"

; The interface files with the dialog resource IDD_INST that contains a bitmap 
; control and space for the header bitmap on the right side.
!define MUI_UI_HEADERIMAGE_RIGHT "${NSISDIR}\Contrib\UIs\modern_headerbmpr.exe"

; The interface files with a customized dialog resource IDD_SELCOM with a small 
; description area.
!define MUI_UI_COMPONENTSPAGE_SMALLDESC "${NSISDIR}\Contrib\UIs\modern_smalldesc.exe"

; The interface files with a customized dialog resource IDD_SELCOM without a 
; description area.
!define MUI_UI_COMPONENTSPAGE_NODESC "${NSISDIR}\Contrib\UIs\modern_nodesc.exe"

; =============================
; Installer welcome/finish page
; =============================

; Bitmap for the Welcome page and the Finish page (recommended size: 164x314 
; pixels).
!define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\win.bmp"

; See MUI_HEADERIMAGE_BITMAP_STRETCH for a list of the available stretch modes.
!define MUI_WELCOMEFINISHPAGE_BITMAP_STRETCH "FitControl"

; ===============================
; Uninstaller welcome/finish page
; ===============================

; Bitmap for the Welcome page and the Finish page (recommended size: 164x314 
; pixels).
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\win.bmp"

; See MUI_HEADERIMAGE_BITMAP_STRETCH for a list of the available stretch modes.
!define MUI_UNWELCOMEFINISHPAGE_BITMAP_STRETCH "FitControl"

; ============
; License page
; ============

; The background color for the license textbox. Use /windows for the Windows 
; text background color (usually white). Use the /grey for the window 
; background color (usually grey).
!define MUI_LICENSEPAGE_BGCOLOR /windows

; ===============
; Components page
; ===============

; The bitmap with images for the checks of the component select treeview.
!define MUI_COMPONENTSPAGE_CHECKBITMAP "${NSISDIR}\Contrib\Graphics\Checks\modern.bmp"

; A small description area on the bottom of the page. Use this layout if you 
; have a lot of sections and don't need large descriptions.
!define MUI_COMPONENTSPAGE_SMALLDESC

; No description area.
!define MUI_COMPONENTSPAGE_NODESC

; ==============
; Directory page
; ==============

; The background color for the directory textbox.
!define MUI_DIRECTORYPAGE_BGCOLOR FFFFFF

; ======================
; Start Menu folder page
; ======================

; The background color for the startmenu directory list and textbox.
!define MUI_STARTMENUPAGE_BGCOLOR FFFFFF

; =================
; Installation page
; =================

; The colors of the details screen. Use /windows for the default Windows colors.
; (/windows | "(foreground color: RRGGBB hexadecimal) (background color: RRGGBB 
; hexadecimal)")
!define MUI_INSTFILESPAGE_COLORS /windows

; The style of the progress bar. Colored makes it use the MUI_INSTALLCOLORS.
; ("" | colored | smooth)
!define MUI_INSTFILESPAGE_PROGRESSBAR smooth

; =====================
; Installer finish page
; =====================

; Do not automatically jump to the finish page, to allow the user to check the 
; install log.
!define MUI_FINISHPAGE_NOAUTOCLOSE

; =======================
; Uninstaller finish page
; =======================

; Do not automatically jump to the finish page, to allow the user to check the 
; uninstall log.
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

; =============
; Abort warning
; =============

; Show a message box with a warning when the user wants to close the installer.
!define MUI_ABORTWARNING

; Text to display on the abort warning message box.
!define MUI_ABORTWARNING_TEXT "Are you sure you want to abort?"

; Set the Cancel button as the default button on the message box.
!define MUI_ABORTWARNING_CANCEL_DEFAULT

; =========================
; Uninstaller abort warning
; =========================

; Show a message box with a warning when the user wants to close the 
; uninstaller.
!define MUI_UNABORTWARNING

; Text to display on the abort warning message box.
!define MUI_UNABORTWARNING_TEXT "Are you sure you want to abort?"

; Set the Cancel button as the default button on the message box.
!define MUI_UNABORTWARNING_CANCEL_DEFAULT

; =====
; Pages
; =====

; Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE.rtf"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
Var StartMenuFolder
!insertmacro MUI_PAGE_STARTMENU "Application" $StartMenuFolder
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_LICENSE "LICENSE.rtf"
!insertmacro MUI_UNPAGE_COMPONENTS
!insertmacro MUI_UNPAGE_DIRECTORY
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; =============
; Page settings
; =============
; Page settings apply to a single page and should be set before inserting a 
; page macro. Repeat the setting to apply to multiple pages.
;
; Example:
; ;Add a directory page to let the user specify a plug-ins folder
; ;Store the folder in $PluginsFolder
;
; Var PluginsFolder
; !define MUI_DIRECTORYPAGE_VARIABLE $PluginsFolder
; !insertmacro MUI_PAGE_DIRECTORY

; =====================
; General page settings
; =====================

; Text to display on the header of the page.
!define MUI_PAGE_HEADER_TEXT "Text to display on the header of the page"

; Subtext to display on the header of the page.
!define MUI_PAGE_HEADER_SUBTEXT "Subtext to display on the header of the page"

; =====================
; Welcome page settings
; =====================

; Title to display on the top of the page.
!define MUI_WELCOMEPAGE_TITLE "Title to display on the top of the page"

; Extra space for the title area.
!define MUI_WELCOMEPAGE_TITLE_3LINES

; Text to display on the page.
!define MUI_WELCOMEPAGE_TEXT "Text to display on the page"

; =====================
; License page settings
; =====================

; Text to display on the top of the page.
!define MUI_LICENSEPAGE_TEXT_TOP "Text to display on the top of the page"

; Text to display on the bottom of the page.
!define MUI_LICENSEPAGE_TEXT_BOTTOM "Text to display on the bottom of the page"

; Text to display on the 'I Agree' button.
!define MUI_LICENSEPAGE_BUTTON "I Agree"

; Display a checkbox the user has to check to agree with the license terms.
!define MUI_LICENSEPAGE_CHECKBOX

; Text to display next to the checkbox to agree with the license terms.
!define MUI_LICENSEPAGE_CHECKBOX_TEXT "Text to display next to the checkbox to agree with the license terms"

; Display two radio buttons to allow the user to choose between accepting the 
; license terms or not.
!define MUI_LICENSEPAGE_RADIOBUTTONS

; Text to display next to the checkbox to accept the license terms.
!define MUI_LICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT "I accept"

; Text to display next to the checkbox to decline the license terms.
!define MUI_LICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE "I decline"

; ========================
; Components page settings
; ========================

; Text to display on the top of the page.
!define MUI_COMPONENTSPAGE_TEXT_TOP "Text to display on the top of the page"

; Text to display on next to the components list.
!define MUI_COMPONENTSPAGE_TEXT_COMPLIST "Text to display on next to the components list"

; Text to display on next to the installation type combo box.
!define MUI_COMPONENTSPAGE_TEXT_INSTTYPE "Text to display on next to the installation type combo box"

; Text to display on the of the top of the description box.
!define MUI_COMPONENTSPAGE_TEXT_DESCRIPTION_TITLE "Text to display on the of the top of the description box"

; Text to display inside the description box when no section is selected.
!define MUI_COMPONENTSPAGE_TEXT_DESCRIPTION_INFO "Text to display inside the description box when no section is selected"

; =======================
; Directory page settings
; =======================

; Text to display on top of the page.
!define MUI_DIRECTORYPAGE_TEXT_TOP "Text to display on top of the page"

; Text to display on the destination folder frame.
!define MUI_DIRECTORYPAGE_TEXT_DESTINATION "Text to display on the destination folder frame"

; Variable in which to store the selected folder.
!define MUI_DIRECTORYPAGE_VARIABLE $INSTDIR

; Does not disable the Next button when a folder is invalid but allows you to 
; use GetInstDirError in the leave function to handle an invalid folder.
!define MUI_DIRECTORYPAGE_VERIFYONLEAVE

; ===============================
; Start Menu folder page settings
; ===============================

; Text to display on the top of the page.
!define MUI_STARTMENUPAGE_TEXT_TOP "Text to display on the top of the page"

; Text to display next to the checkbox to disable the Start Menu folder 
; creation.
!define MUI_STARTMENUPAGE_TEXT_CHECKBOX "Text to display next to the checkbox to disable the Start Menu folder creation"

; The default Start Menu Folder.
!define MUI_STARTMENUPAGE_DEFAULTFOLDER ""

; Do not display the checkbox to disable the creation of Start Menu shortcuts.
!define MUI_STARTMENUPAGE_NODISABLE

; The registry key to store the Start Menu folder. The page will use it to 
; remember the users preference. You should also use for the uninstaller to 
; remove the Start Menu folders. Don't forget to remove this key during 
; uninstallation.
; !define MUI_STARTMENUPAGE_REGISTRY_ROOT root
; !define MUI_STARTMENUPAGE_REGISTRY_KEY key
; !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME value_name

; For the uninstaller, use the MUI_STARTMENU_GETFOLDER macro to get the Start 
; Menu folder:
;
; !insertmacro MUI_STARTMENU_GETFOLDER page_id $R0
; Delete "$SMPROGRAMS\$R0\Your Shortcut.lnk"

; ==========================
; Installation page settings
; ==========================

; Text to display on the header of the installation page when the installation 
; has been completed (won't be displayed when using a Finish page without 
; MUI_(UN)FINISHPAGE_NOAUTOCLOSE).
!define MUI_INSTFILESPAGE_FINISHHEADER_TEXT "Installation completed"

; Subtext to display on the header of the installation page when the 
; installation has been completed (won't be displayed when using a Finish page 
; without MUI_(UN)FINISHPAGE_NOAUTOCLOSE).
!define MUI_INSTFILESPAGE_FINISHHEADER_SUBTEXT "Congratulations! You may start using the software now."

; Text to display on the header of the installation page when the installation has been aborted.
!define MUI_INSTFILESPAGE_ABORTHEADER_TEXT "Installation aborted"

; Subext to display on the header of the installation page when the installation has been aborted.
!define MUI_INSTFILESPAGE_ABORTHEADER_SUBTEXT  "Installation has been aborted at your request."

; ====================
; Finish page settings
; ====================

; Title to display on the top of the page.
!define MUI_FINISHPAGE_TITLE "Title to display on the top of the page"

; Extra space for the title area.
!define MUI_FINISHPAGE_TITLE_3LINES

; Text to display on the page.
!define MUI_FINISHPAGE_TEXT "Text to display on the page"

; Extra space for the text area (if using checkboxes).
!define MUI_FINISHPAGE_TEXT_LARGE

; Text to display on the Finish button.
!define MUI_FINISHPAGE_BUTTON "Finish"

; Enable the Cancel button so the user can skip any options displayed on the 
; finish page.
!define MUI_FINISHPAGE_CANCEL_ENABLED

; Text to display on the finish page when asking for a system reboot.
!define MUI_FINISHPAGE_TEXT_REBOOT "Text to display on the finish page when asking for a system reboot"

; Text to display next to the 'Reboot now' option button.
!define MUI_FINISHPAGE_TEXT_REBOOTNOW "Reboot now"

; Text to display next to the 'Reboot later' option button.
!define MUI_FINISHPAGE_TEXT_REBOOTLATER "Reboot later"

; Sets the 'Reboot later' option as the default option.
!define MUI_FINISHPAGE_REBOOTLATER_DEFAULT

; Application which the user can select to run using a checkbox. You don't need 
; to put quotes around the filename when it contains spaces.
!define MUI_FINISHPAGE_RUN run-an-app.exe

; Texts to display next to the 'Run program' checkbox.
!define MUI_FINISHPAGE_RUN_TEXT "Run program run-an-app.exe"

; Parameters for the application to run. Don't forget to escape double quotes 
; in the value (use $\").
!define MUI_FINISHPAGE_RUN_PARAMETERS "/a /b $\"quoted value$\" /c test"

; Do not check the 'Run program' checkbox by default
!define MUI_FINISHPAGE_RUN_NOTCHECKED

; Call a function instead of executing an application (define 
; MUI_FINISHPAGE_RUN without parameters). You can use the function to execute 
; multiple applications or you can change the checkbox name and use it for 
; other things.
!define MUI_FINISHPAGE_RUN_FUNCTION runfunction

; File or website which the user can select to view using a checkbox. You don't 
; need to put quotes around the filename when it contains spaces.
!define MUI_FINISHPAGE_SHOWREADME "README.txt"

; Texts to display next to the 'Show Readme' checkbox.
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Texts to display next to the 'Show Readme' checkbox"

; Do not check the 'Show Readme' checkbox by default
!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED

; Call a function instead of showing a file (define MUI_FINISHPAGE_SHOWREADME 
; without parameters). You can use the function to show multiple files or you 
; can change the checkbox name and use it for other things.
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION showreadmefunction

; Text for a link on the which the user can click to view a website or file.
!define MUI_FINISHPAGE_LINK "Click to open link"

; Website or file which the user can select to view using the link. You don't 
; need to put quotes around the filename when it contains spaces.
!define MUI_FINISHPAGE_LINK_LOCATION "https://app.landing.page.example.test/"

; Text color for the link on the Finish page.
!define MUI_FINISHPAGE_LINK_COLOR 000080

; Disables support for the page that allows the user to reboot the system. 
; Define this option to save some space if you are not using the /REBOOTOK flag 
; or SetRebootFlag.
!define MUI_FINISHPAGE_NOREBOOTSUPPORT

; ===============================
; Uninstall confirm page settings
; ===============================

; Text to display on the top of the page.
!define MUI_UNCONFIRMPAGE_TEXT_TOP "Text to display on the top of the page"

; Text to display next to the uninstall location text box.
!define MUI_UNCONFIRMPAGE_TEXT_LOCATION "Text to display next to the uninstall location text box"

; Variable in which to store the uninstall source folder.
!define MUI_UNCONFIRMPAGE_VARIABLE $INSTDIR

; ============================
; Components page descriptions
; ============================

Section "Section Name 1" Section1
   ...
SectionEnd

Section "Section Name 2" Section2
   ...
SectionEnd

LangString DESC_Section1 ${LANG_ENGLISH} "Description of section 1."
LangString DESC_Section2 ${LANG_ENGLISH} "Description of section 2."

; For installer (note MUI_FUNCTION_*)
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${Section1} $(DESC_Section1)
  !insertmacro MUI_DESCRIPTION_TEXT ${Section2} $(DESC_Section2)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

; For uninstaller (note MUI_UNFUNCTION_*)
!insertmacro MUI_UNFUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${Section1} $(DESC_Section1)
  !insertmacro MUI_DESCRIPTION_TEXT ${Section2} $(DESC_Section2)
!insertmacro MUI_UNFUNCTION_DESCRIPTION_END

; =================
; Start Menu folder
; =================

; The page ID should be the ID of the page on which the user has selected the 
; folder for the shortcuts you want to write.

!insertmacro MUI_STARTMENU_WRITE_BEGIN pageid
  ...create shortcuts...
  CreateShortcut ...
  CreateShortcut ...
  CreateShortcut ...
  CreateShortcut ...
  CreateShortcut ...
  ...create shortcuts...
!insertmacro MUI_STARTMENU_WRITE_END

; =========================
; Language selection dialog
; =========================

; If you want the installer to display a language selection dialog (see the the 
; MultiLanguage.nsi example), insert the MUI_LANGDLL_DISPLAY macro in the 
; .onInit function:

; Installer
Function .onInit

  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

; Uninstaller
Function un.onInit

  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

; ==================================================
; Settings for registry storage of selected language
; ==================================================

; To remember the user's preference, you can define a registry key. These 
; defines should be set before inserting the installation page macro.

!define MUI_LANGDLL_REGISTRY_ROOT root
!define MUI_LANGDLL_REGISTRY_KEY key
!define MUI_LANGDLL_REGISTRY_VALUENAME value_name

; Uninstaller

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE

FunctionEnd

; =======================================
; Interface settings for selection dialog
; =======================================

; To customize the language selection dialog interface, use these defines 
; ** BEFORE ** inserting the MUI_LANGDLL_DISPLAY macro.

; The window title of the language selection dialog.
!define MUI_LANGDLL_WINDOWTITLE "The window title of the language selection dialog"

; The text to display on the language selection dialog.
!define MUI_LANGDLL_INFO "The text to display on the language selection dialog"

; Always show the language selection dialog, even if a language has been stored 
; in the registry. The language stored in the registry will be selected by 
; default.
!define MUI_LANGDLL_ALWAYSSHOW

; Always show all available languages and don't filter according to their 
; codepage.
!define MUI_LANGDLL_ALLLANGUAGES

; ============
; Custom pages
; ============

; If you want add your custom pages to your installer, you can insert your own 
; page commands between the page macros.

!insertmacro MUI_PAGE_WELCOME
Page custom FunctionName ;Custom page
!insertmacro MUI_PAGE_COMPONENTS
 
;Uninstaller
!insertmacro MUI_UNPAGE_CONFIRM
UninstPage custom un.FunctionName ;Custom page
!insertmacro MUI_UNPAGE_INSTFILES

; Use the MUI_HEADER_TEXT macro to set the text on the page header in a page 
; function:

LangString PAGE_TITLE ${LANG_ENGLISH} "Title"
LangString PAGE_SUBTITLE ${LANG_ENGLISH} "Subtitle"

Function CustomPageFunction
  !insertmacro MUI_HEADER_TEXT $(PAGE_TITLE) $(PAGE_SUBTITLE)
  nsDialogs::...
  ...
FunctionEnd

; ================
; Custom functions
; ================

; To add additional code to interface functions provided by NSIS (e.g. 
; .onGUIInit function and page function), create a function with the custom 
; script code, and call it from Modern UI functions. 

; Example

!define MUI_CUSTOMFUNCTION_GUIINIT myGuiInit

Function myGUIInit
  ...
FunctionEnd

; Hook custom function

; ========================
; General Custom Functions
; ========================

!define MUI_CUSTOMFUNCTION_GUIINIT myGuiInit
!define MUI_CUSTOMFUNCTION_UNGUIINIT myUnGuiInit
!define MUI_CUSTOMFUNCTION_ABORT myAbort
!define MUI_CUSTOMFUNCTION_UNABORT myUnAbort
!define MUI_CUSTOMFUNCTION_ONMOUSEOVERSECTION myOnMouseOverSection
!define MUI_CUSTOMFUNCTION_UNONMOUSEOVERSECTION myUnOnMouseOverSection

; =====================
; Page Custom Functions
; =====================

; These defines should be set ** BEFORE ** inserting a page macro.

!define MUI_PAGE_CUSTOMFUNCTION_PRE myPre
!define MUI_PAGE_CUSTOMFUNCTION_SHOW myShow
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE myLeave
!define MUI_PAGE_CUSTOMFUNCTION_DESTROYED myDestroyed




