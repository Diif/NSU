import 'package:testflutter/pages/main/model/supply_order.dart';

class ChangeableSupplyOrder{
  int? id;
  DateTime? time;
  int? subId;
  String? subName;
  int? countToReceive;
  int? receivedCount;

  ChangeableSupplyOrder();

  ChangeableSupplyOrder.fromSupplyOrder(SupplyOrder supplyOrder){
    id = supplyOrder.id;
    time = supplyOrder.time;
    subId = supplyOrder.subId;
    subName = supplyOrder.subName;
    countToReceive = supplyOrder.countToReceive;
    receivedCount = supplyOrder.receivedCount;
  }

}