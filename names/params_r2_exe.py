# Parameter names of GRIMFANDANGO.EXE functions (tools/names_batch.py), round 2: the live param_N left
N = {
 # costume tag requesters: (cosInst, tag, parent, type, file name or NULL to ask for one)
 'BitmapRequester': [None, None, None, None, 'filename'],
 'ColormapRequester': [None, None, None, None, 'filename'],
 'ThingRequester': [None, None, None, None, 'filename'],
 'KeyframeRequester': [None, None, None, None, 'filename'],
 'SpriteRequester': ['cosInst', 'tag', 'parent', 'type', 'filename'],
 # lua_restorehook(tag, saved id): the id becomes the object's pointer
 'sputLua_RestoreIndirector': [None, 'id'],
 # DLGTEMPLATE (style, cdit, x, y, cx, cy), the title, the font name and point size (DS_SETFONT when a font is
 # given), out: the template's size
 'Dlg_MakeDialogTemplate': ['style', 'items', 'x', 'y', 'cx', 'cy', 'title', 'font', 'pointSize', 'outSize'],
 'text_FindNextBreak': ['context', None, None, None, None, None],
}
