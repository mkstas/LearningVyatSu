import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import '../models/work.dart';

class DatabaseHelper {
  static final DatabaseHelper instance = DatabaseHelper._init();
  static Database? _database;

  DatabaseHelper._init();

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDatabase();
    return _database!;
  }

  Future<Database> _initDatabase() async {
    final dbPath = await getDatabasesPath();
    final path = join(dbPath, 'works_app.db');

    return await openDatabase(
      path,
      version: 1,
      onCreate: _createDatabase,
    );
  }

  Future<void> _createDatabase(Database db, int version) async {
    await db.execute('''
      CREATE TABLE work_types (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL UNIQUE
      )
    ''');

    await db.execute('''
      CREATE TABLE academic_works (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT NOT NULL,
        description TEXT,
        work_type_id INTEGER NOT NULL,
        due_date TEXT NOT NULL,
        FOREIGN KEY (work_type_id) REFERENCES work_types (id)
      )
    ''');

    await db.insert('work_types', {'name': 'Практическая'});
    await db.insert('work_types', {'name': 'Лабораторная'});
    await db.insert('work_types', {'name': 'Курсовая'});
  }

  Future<void> initDatabase() async {
    await database;
  }

  Future<List<WorkType>> getWorkTypes() async {
    final db = await database;
    final maps = await db.query('work_types');
    return maps.map((map) => WorkType.fromMap(map)).toList();
  }

  Future<int> insertAcademicWork(AcademicWork work) async {
    final db = await database;
    return await db.insert('academic_works', work.toMapWithoutId());
  }

  Future<List<AcademicWork>> getAllAcademicWorks() async {
    final db = await database;
    final maps = await db.query('academic_works', orderBy: 'due_date ASC');
    final works = <AcademicWork>[];

    for (var map in maps) {
      final work = AcademicWork.fromMap(map);
      final typeMaps = await db.query(
        'work_types',
        where: 'id = ?',
        whereArgs: [work.workTypeId],
      );
      if (typeMaps.isNotEmpty) {
        work.workTypeName = typeMaps.first['name'] as String;
      }
      works.add(work);
    }

    return works;
  }

  Future<AcademicWork?> getAcademicWork(int id) async {
    final db = await database;
    final maps = await db.query(
      'academic_works',
      where: 'id = ?',
      whereArgs: [id],
    );

    if (maps.isNotEmpty) {
      final work = AcademicWork.fromMap(maps.first);
      final typeMaps = await db.query(
        'work_types',
        where: 'id = ?',
        whereArgs: [work.workTypeId],
      );
      if (typeMaps.isNotEmpty) {
        work.workTypeName = typeMaps.first['name'] as String;
      }
      return work;
    }
    return null;
  }

  Future<int> updateAcademicWork(AcademicWork work) async {
    final db = await database;
    return await db.update(
      'academic_works',
      work.toMapWithoutId(),
      where: 'id = ?',
      whereArgs: [work.id],
    );
  }

  Future<int> deleteAcademicWork(int id) async {
    final db = await database;
    return await db.delete(
      'academic_works',
      where: 'id = ?',
      whereArgs: [id],
    );
  }

  Future close() async {
    final db = await database;
    db.close();
  }
}