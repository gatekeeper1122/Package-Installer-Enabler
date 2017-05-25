white = Color.new(255,255,255,255) -- Create a new color
if System.doesFileExist("vs0:/app/NPXS10031/pkgpatched")==false then
    if System.doesFileExist("ux0:/test.txt")==false then
        fileStream = io.open("ux0:/test.txt",FCREATE)
        System.launchEboot("app0:/VitaRW_for_LUA.bin")
    else
        System.deleteFile("ux0:/test.txt")
        System.extractZIP("app0:/pkgpatch.zip", "vs0:/app/NPXS10031")
        System.launchEboot("app0:/reboot.bin")
    end
else
    while true do
	Graphics.initBlend()
	Screen.clear()
	Graphics.debugPrint(5, 5, "If The Package Installer Throws An Error Press 'OK' And Then Start It Again Manually", white)
	Graphics.debugPrint(5, 45, "X: Launch Package Installer", white)
	Graphics.termBlend()
	Screen.flip()
    if Controls.check(Controls.read(), SCE_CTRL_CROSS) then
    System.executeUri("psgm:play?titleid=NPXS10031")
	end
    end
    
end
