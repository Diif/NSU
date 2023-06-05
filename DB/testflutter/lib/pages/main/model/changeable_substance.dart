import 'package:testflutter/pages/main/model/substance.dart';

class ChangeableSubstance {
  int? id;
  String? name;
  int? categoryId;
  String? categoryName;
  int? critCount;
  int? count;
  String? pricePcs;

  ChangeableSubstance();

  ChangeableSubstance.fromSub(Substance sub, String this.categoryName){
    id = sub.id;
    name = sub.name;
    categoryId = sub.categoryId;
    critCount = sub.critCount;
    count = sub.count;
    pricePcs = sub.pricePcs;
  }

}
