#include "innerproduct.h"

int32_t test_inner_product_circuit(e_role role, char * address, uint16_t port, seclvl seclvl, uint32_t nvals, 
    uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg, e_sharing sharing, uint32_t r, uint32_t c)
{
    // Initialization.
    ABYParty * party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg);
    vector<Sharing*>&sharings = party -> GetSharings();
    sharings[S_BOOL]->SetPreCompPhaseValue(ePreCompPhase::ePreCompRead);
    BooleanCircuit *circ = (BooleanCircuit*) sharings[sharing] -> GetCircuitBuildRoutine();
    share *s_x_vec, *s_y_vec, *res;
    uint8_t x, y;

    // Total number of elements in matrix.
    uint32_t num = r * c;

    // Create x / y values array.
    uint8_t * xvals = (uint8_t * ) malloc((num + 1) * sizeof(uint8_t));  // Num + 1 is for the magic number "0".
    uint8_t * yvals = (uint8_t * ) malloc((num + 1) * sizeof(uint8_t));

    // Fill the matrix according to role.
    uint32_t i;
    if (role == SERVER)
      srand(1000);
    else
      srand(2000);
    for (i = 0; i < num; i++) {
      x = rand() % 2;
      xvals[i] = x;
    }
    xvals[num] = 0;  // For the use of PutSUBSETGate.
    for (i = 0; i < num; i++) {
      y = rand() % 2;
      yvals[i] = y;
    }
    yvals[num] = 0;  // For the use of PutSUBSETGate.

    // Put arrays in gate as SIMD shares.
    s_x_vec = circ -> PutSharedSIMDINGate(num + 1, xvals, bitlen);
    s_y_vec = circ -> PutSharedSIMDINGate(num + 1, yvals, bitlen);

    res = circ -> PutANDGate(s_x_vec, s_y_vec);

    // Summing up products to get dot products
    int e = 1;
    while (e < c)
        e = e << 1;
    e = e >> 1;
    uint32_t * pos1 = new uint32_t[e * r];
    uint32_t * pos2 = new uint32_t[e * r];
    int ind1 = 0;
    int ind2 = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < e; j++)
        {
            pos1[ind1++] = (i * c) + j;  // The first part of the segmentation.
        }
        // The indices in the second half part.
        for (int j = e; j < c; j++)
            pos2[ind2++] = (i * c) + j;  // The rest of the segmentation.
        for (int j = c; j < (2 * e); j++)
            pos2[ind2++] = num;  // Set the very last index to the "0".

    }
    share * part1 = circ -> PutSubsetGate(res, pos1, e * r);
    share * part2 = circ -> PutSubsetGate(res, pos2, e * r);

    delete[] pos1;
    delete[] pos2;

    res = circ -> PutADDGate(part1, part2);
    e = e >> 1;
    while (e >= 1)
    {
        uint32_t * p1 = new uint32_t[e * r];
        uint32_t * p2 = new uint32_t[e * r];
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < e; j++)
            {
                p1[(i * e) + j] = ((i * e * 2) + j);
            }
            for (int j = e; j < (2 * e); j++)
                p2[(i * e) + (j - e)] = (i * e * 2) + j;
        }
        part1 = circ -> PutSubsetGate(res, p1, e * r);
        part2 = circ -> PutSubsetGate(res, p2, e * r);

        delete[] p1;
        delete[] p2;
        res = circ -> PutADDGate(part1, part2);

        e = e >> 1;
    }
    
  
    res = circ -> PutSharedOUTGate(res);

    party -> ExecCircuit();

    uint32_t out_bitlen, out_nvals, * out_vals;
    res -> get_clear_value_vec( & out_vals, & out_bitlen, & out_nvals);

    //for (int i=0;i<out_nvals;i++)
    //      cout<<out_vals[i]<<" ";
    //cout<<endl;

    free(xvals);
    free(yvals);
    delete party;

    return 0;
}