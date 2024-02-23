function filedialog(filt, directory, title, save, defExt)
    set dialog = CreateObject("MSComDlg.CommonDialog")
    dialog.MaxFileSize = 256
    if filt = "" then
        dialog.Filter = "All Files (*.*)|*.*"
    else
        dialog.Filter = filt
    end if
    dialog.FilterIndex = 1
    dialog.DialogTitle = title
    ' dialog.InitDir = CreateObject("WScript.Shell").SpecialFolders("MyDocuments")
    dialog.InitDir = directory
    dialog.FileName = ""
    if save = true then
        dialog.DefaultExt = defExt
        dialog.Flags = &H800 + &H4
        discard = dialog.ShowSave()
    else
        dialog.Flags = &H1000 + &H4 + &H800
        discard = dialog.ShowOpen()
    end if
    filedialog = dialog.FileName
end function
