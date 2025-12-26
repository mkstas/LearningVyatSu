import 'package:intl/intl.dart';

class WorkType {
  int id;
  String name;

  WorkType({
    required this.id,
    required this.name,
  });

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'name': name,
    };
  }

  factory WorkType.fromMap(Map<String, dynamic> map) {
    return WorkType(
      id: map['id'] as int,
      name: map['name'] as String,
    );
  }
}

class AcademicWork {
  int id;
  String title;
  String description;
  int workTypeId;
  String workTypeName;
  DateTime dueDate;

  AcademicWork({
    this.id = 0,
    required this.title,
    required this.description,
    required this.workTypeId,
    this.workTypeName = '',
    required this.dueDate,
  });

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'title': title,
      'description': description,
      'work_type_id': workTypeId,
      'due_date': DateFormat('yyyy-MM-dd').format(dueDate),
    };
  }

  Map<String, dynamic> toMapWithoutId() {
    return {
      'title': title,
      'description': description,
      'work_type_id': workTypeId,
      'due_date': DateFormat('yyyy-MM-dd').format(dueDate),
    };
  }

  factory AcademicWork.fromMap(Map<String, dynamic> map) {
    return AcademicWork(
      id: map['id'] as int,
      title: map['title'] as String,
      description: map['description'] as String,
      workTypeId: map['work_type_id'] as int,
      dueDate: DateFormat('yyyy-MM-dd').parse(map['due_date'] as String),
    );
  }

  String get formattedDate {
    return DateFormat('dd.MM.yyyy').format(dueDate);
  }

  String get formattedDateFull {
    return DateFormat('dd MMMM yyyy', 'ru_RU').format(dueDate);
  }
}