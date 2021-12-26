# Firmware_Decrypt
This utility is used to decrypt firmware.
Currently only tested for IAW5000 Series PLC V2.2
I plan on expanding on it as i reverse more firmware

### Here is the firmware Pre-Decryption
<pre>
$ binwalk fw.rom 
 
DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
</pre>

### Here is the firmware Post-Decryption
<pre>
$ binwalk final.rom<br />

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------<br />
48            0x30            Linux kernel ARM boot executable zImage (little-endian)<br />
8148          0x1FD4          LZO compressed data<br />
8625          0x21B1          LZO compressed data<br />
596004        0x91824         mcrypt 2.5 encrypted data, algorithm: "!", keysize: 5554 bytes, mode: "\",<br />
1429474       0x15CFE2        Linux kernel version 2.6.31<br />
1435344       0x15E6D0        gzip compressed data, maximum compression, from Unix, last modified: 2020-06-29 07:51:08<br />
1929421       0x1D70CD        mcrypt 2.5 encrypted data, algorithm: "\", keysize: 109 bytes, mode: "t",<br />
1956736       0x1DDB80        Zlib compressed data, best compression<br />
2030833       0x1EFCF1        Zlib compressed data, best compression<br />
... truncated
</pre>
