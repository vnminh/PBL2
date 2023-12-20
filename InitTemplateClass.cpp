#include "DNode.cpp"
#include "DList.cpp"
#include "Product.h"
#include "DetailProduct.h"
#include "DetailWeightProduct.h"
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
template  DetailProduct* FindIndex<DetailProduct>(const DList<DetailProduct*>&, const int&);
template void QuickSort<Product, int>(DNode<Product*>*, DNode<Product*>*, int(Product::*)() const, int);
template DNode<Product*>* Partition<Product, int>(DNode<Product*>*, DNode<Product*>*, int(Product::*)() const, int);