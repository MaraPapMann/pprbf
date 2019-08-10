#include "innerproduct.h"

int32_t test_inner_product_circuit(e_role role, char * address, uint16_t port, seclvl seclvl,uint32_t nvals, 
    uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,e_sharing sharing, uint32_t r, uint32_t c)
{
    // Initialization.
    ABYParty * party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg);
    vector<Sharing*>&sharings = party -> GetSharings();
    ArithmeticCircuit *circ = (ArithmeticCircuit*) sharings[sharing] -> GetCircuitBuildRoutine();
    share * s_x_vec, * s_y_vec, * res;
    uint8_t x, y;

    // Total number of elements in matrix.
    uint32_t num = r * c;

    // Create x / y values array.
    uint8_t * xvals = (uint8_t * ) malloc((num) * sizeof(uint8_t));
    uint8_t * yvals = (uint8_t * ) malloc((num) * sizeof(uint8_t));

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
    for (i = 0; i < num; i++) {
      y = rand() % 2;
      yvals[i] = y;
    }

    // Put arrays in gate as SIMD shares.
    s_x_vec = circ -> PutSharedSIMDINGate(num, xvals, bitlen);
    s_y_vec = circ -> PutSharedSIMDINGate(num, yvals, bitlen);

    s_x_vec = circ->PutMULGate(s_x_vec, s_y_vec); // Now each nval is a value, need to be transposed so that each wire stands for one value.
    s_x_vec = circ->PutSplitterGate(s_x_vec); // Transposed.

    // Summing up products for each dot product.
    for(int i=0; i< num/c; i++)
    {
      int idx = i*c;
      for(int j=1; j<c; j++)
      {
        s_x_vec->set_wire_id(idx, circ->PutADDGate(s_x_vec->get_wire_id(idx), s_x_vec->get_wire_id(idx+j))); // Put the summation result into the right pos
      }
    }

    // Setting dot products into the front of the share.
    for(int i=0; i<num/c; i++)
    {
      s_x_vec->set_wire_id(i, s_x_vec->get_wire_id(i*c));
    }

    // Discard all unnecessary wires except for the dot products.
    s_x_vec->set_bitlength(num/c);


    res = circ -> PutSharedOUTGate(s_x_vec);

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