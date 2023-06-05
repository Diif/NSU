import 'package:testflutter/pages/main/model/tech_with_sub.dart';

class ChangeableTech{
  int? id;
  String? medicineName;
  String? description;
  Duration? creationTime;
  int? medCount;

  ChangeableTech();

  ChangeableTech.fromTech(TechWithSub t){
    id = t.id;
    medicineName = t.medicineName;
    description = t.description;
    creationTime = t.creationTime;
    medCount = t.medCount;
  }
}