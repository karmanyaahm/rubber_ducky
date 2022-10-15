$Path=Resolve-Path "~\oreo2.png"

# https://c-nergy.be/blog/?p=17309
#--------------------------------------------------------------------------------------------------#
# ScriptName : Update-WallPaper.ps1                                                                #
# Description : Force a Desktop wallpaper Refresh with no logoff/login needed                      #
# Date : December 2021                                                                             #
# Written : Griffon                                                                                #
# WebSite :http://www.c-nergy.be - http://www.c-nergy.be/blog                                      #
# Version : 2.0                                                                                    #
# History : 2.0  - Adding functions and parameters to cover more scenario                          #
#         : 1.0  - Initial Version - Basic Settings                                                #
#                                                                                                  #
# Credits  : Unknown (multipe Internet Sources & References)                                       #
#                                                                                                  #
# Notes : We have been using multiple resources from internet and cope snippets in order to come   #
#         with this script...The following link has provided us really good base and info to build #
#         up the script (https://stackoverflow.com/questions/19989906/ how-to-set-wallpaper-style  #
#          -fill-stretch-according-to-windows-version).                                            #
#                                                                                                  #
# Disclaimer : Script provided AS IS. Use it at your own risk....                                  #
#              You can use this script and distribute it as long as credits are kept               #
#              in place and unchanged                                                              #
#                                                                                                  #
#--------------------------------------------------------------------------------------------------#

<#
Credits/ info from https://stackoverflow.com/questions/19989906/how-to-set-wallpaper-style-fill-stretch-according-to-windows-version
 ' Set the wallpaper style and tile.
        ' Two registry values are set in the Control Panel\Desktop key.
        ' TileWallpaper
        '  0: The wallpaper picture should not be tiled
        '  1: The wallpaper picture should be tiled
        ' WallpaperStyle
        '  0:  The image is centered if TileWallpaper=0 or tiled if TileWallpaper=1
        '  2:  The image is stretched to fill the screen
        '  6:  The image is resized to fit the screen while maintaining the aspect
        '      ratio. (Windows 7 and later)
        '  10: The image is resized and cropped to fill the screen while
        '      maintaining the aspect ratio. (Windows 7 and later)
        '  22: Span image
#>


$Wstyle = @{
            'Centered'  = 0
            'Stretched' = 2
            'Fill'      = 10
            'Fit'       = 6
            'Span'      = 22
}

$WTile = @{
            'Tiles'     = 1
            'NoTiles'   = 0
        }

    #Main Code
    $code = @'
    using System.Runtime.InteropServices;
    namespace Win32{
     public class Wallpaper{
        [DllImport("user32.dll", CharSet=CharSet.Auto)]
         static extern int SystemParametersInfo (int uAction , int uParam , string lpvParam , int fuWinIni) ;
         public static void SetWallpaper(string thePath){
            SystemParametersInfo(20,0,thePath,3);
         }
    }
 }
'@

if ($error[0].exception -like "*Cannot add type. The type name 'Win32.Wallpaper' already exists.*")
{
    write-host "Win32.Wallpaer assemblies already loaded"
    write-host "Proceeding"
} else {
    add-type $code
}

# Code for settings TileStyle and Wallpaper Style
Set-ItemProperty -Path 'HKCU:\Control Panel\Desktop' -Name wallpaperstyle -Value $Wstyle['Fit']
Set-ItemProperty -Path 'HKCU:\Control Panel\Desktop' -Name TileWallpaper -Value $WTile['NoTiles']

#Apply the Change on the system
[Win32.Wallpaper]::SetWallpaper($Path)

# lock screen
[Windows.System.UserProfile.LockScreen,Windows.System.UserProfile,ContentType=WindowsRuntime] | Out-Null
Add-Type -AssemblyName System.Runtime.WindowsRuntime

$asTaskGeneric = ([System.WindowsRuntimeSystemExtensions].GetMethods() | Where-Object { $_.Name -eq 'AsTask' -and $_.GetParameters().Count -eq 1 -and $_.GetParameters()[0].ParameterType.Name -eq 'IAsyncOperation`1' })[0]

Function Await($WinRtTask, $ResultType) {
    $asTask = $asTaskGeneric.MakeGenericMethod($ResultType)
    $netTask = $asTask.Invoke($null, @($WinRtTask))
    $netTask.Wait(-1) | Out-Null
    $netTask.Result
}
Function AwaitAction($WinRtAction) {
    $asTask = ([System.WindowsRuntimeSystemExtensions].GetMethods() | Where-Object { $_.Name -eq 'AsTask' -and $_.GetParameters().Count -eq 1 -and !$_.IsGenericMethod })[0]
    $netTask = $asTask.Invoke($null, @($WinRtAction))
    $netTask.Wait(-1) | Out-Null
}

[Windows.Storage.StorageFile,Windows.Storage,ContentType=WindowsRuntime] | Out-Null

$image = Await([Windows.Storage.StorageFile]::GetFileFromPathAsync($Path)) ([Windows.Storage.StorageFile])
AwaitAction([Windows.System.UserProfile.LockScreen]::SetImageFileAsync($image))

exit;
