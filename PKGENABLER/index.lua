    if System.doesFileExist("ux0:/test.txt")==false then
        fileStream = io.open("ux0:/test.txt",FCREATE)
        System.launchEboot("app0:/VitaRW_for_LUA.bin")
    else
        System.deleteFile("ux0:/test.txt")
        -- Create a new color
    white = Color.new(255,255,255,255) 
    end
    
while true do
	
	Graphics.initBlend()
	Screen.clear()
	Graphics.debugPrint(5, 5, "PKGEnabler By SilicaAndPina!", white)
    Graphics.debugPrint(5, 25, "Which PKG Installer Mod Would You Like To Use?", white)
    Graphics.debugPrint(5, 45, "X: DEX PKG INSTALLER (Recommended)", white)
    Graphics.debugPrint(5, 65, "O: MAJOR_TOM PKG INSTALLER (Only use if you know what it is.)", white)
	Graphics.termBlend()
	Screen.flip()
	
	if Controls.check(Controls.read(), SCE_CTRL_CROSS) then
        System.extractZIP("app0:/pkgpatchDEX.zip", "vs0:/app/NPXS10031")
        System.launchEboot("app0:/patch_app_db.bin")
    else if Controls.check(Controls.read(), SCE_CTRL_CIRCLE) then
        System.extractZIP("app0:/pkgpatchMAJOR.zip", "vs0:/app/NPXS10031")
        System.launchEboot("app0:/patch_app_db.bin")
	end
	
end
end
