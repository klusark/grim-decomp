# 0x0048483d-0x0048484b of 1.01 (a0 78 80 4e 00 / a8 02 / 74 09 / 56) were mis-decoded by the export as
# "dec ESI; add byte ptr [EAX+0x56097402],CH" (the first three bytes were skipped).  Restore the real instructions.
s/^\.L484260_484840:\tdec ESI$/.L484260_48483d:\tmov AL,byte ptr [_sect_data+0xb078]\n.L484260_484842:\ttest AL,0x2\n.L484260_484844:\tjz .L484260_48484f\n.L484260_484846:\tpush ESI/
/^\.L484260_484841:\tadd byte ptr \[EAX\+0x56097402\],CH$/d
