# Parameter names of IMUSE.DLL functions (tools/names_batch.py), round 2
N = {
 'DpStartSound': ['track', None],
 # the next chunk with the given id in a map (after prev, or the first)
 'iMUSE_Dispatch__30d0': ['map', 'id', 'prev'],
 # the first JUMP chunk of the map inside the region whose hook passes
 'iMUSE_Dispatch__31d0': ['map', 'region', None],
 'iMUSE_Dispatch__3430': ['dispatch', 'region'],
 'iMUSE_Dispatch__34b0': ['dispatch'],
 'iMUSE_Dispatch__3510': ['dispatch', 'count'],
 # fade buffers: takes one of at most *size bytes (the size given back), frees one
 'iMUSE_Dispatch__35a0': ['size'],
 'iMUSE_Dispatch__3640': ['buf'],
 'iMUSE_sounds__9eb0': ['res', 'offset'],
 'Im_RunDeferredCommand': ['entry'],
}
