    if System.doesFileExist("ux0:/test.txt")==false then
        fileStream = io.open("ux0:/test.txt",FCREATE)
        System.launchEboot("app0:/VitaRW_for_LUA.bin")
    else
        System.deleteFile("ux0:/test.txt")
        System.extractZIP("app0:/pkgpatch.zip", "vs0:/app/NPXS10031")
        System.launchEboot("app0:/patch_app_db.bin")
    end
    
