#include "DNode.cpp"
#include "DList.cpp"
#include "Product.h"
#include "DetailProduct.h"
#include "Customer.h"
#include "Bill.h"
#include "DetailBill.h"
template class DNode < DetailProduct* >;
template class DList < DetailProduct* >;
template class DNode < Product* >;
template class DList < Product* >;
template class DNode < Customer* >;
template class DList < Customer* >;
template class DNode < Bill* >;
template class DList < Bill* >;
template class DNode < DetailBill* >;
template class DList < DetailBill* >;
template  DetailProduct* FindFirstMatch<DetailProduct, String>(const DList<DetailProduct*>&, const String&, String(DetailProduct::*)()const);