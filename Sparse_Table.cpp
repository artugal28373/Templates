For(ir=0;ir<n;ir++)
{
  For(ic=0;ic<m;ic++)
    table[ 0 ][ ir ][ 0 ][ ic ] = Matrix[ ir ][ ic ];
       
  For(jc=1;jc<=log2(m);jc++)
    For(ic=0;ic+2^(jc-1)<m;ic++)
     table[0 ][ir ][jc ][ic ] = min(table[0 ][ir ][jc-1 ][ic ],table[0 ][ir ][ jc-1 ][ ic+2^(jc-1) ])
}    // bse
For(jr=1;jr<=log(n);jr++)
  For(ir=0;ir<n;ir++)
    For(jc=0;jc<=log(m);jc++)
      For(ic=0;ic<m;ic++)
        table[jr ][ir ][jc ][ic ] = min(table[jr-1 ][ir ][jc ][ic ],table[jr-1 ][ir+2^(jr-1) ][jc ][ic ])  
min_R1 = min ( table[kx ][x1 ][ky ][y1 ] , table[kx ][x1 ][ky ][ y2+1-2^ky ] ) 
  min_R2 = min ( table[kx ][x2+1-2^kx ][ky ][y1 ], table[kx ][x2+1-2^kx ][ky ][y2+1-2^ky ] )
  return min ( min_R1, min_R2 )
