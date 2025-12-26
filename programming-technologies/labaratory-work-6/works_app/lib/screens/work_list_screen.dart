import 'package:flutter/material.dart';
import '../database/database_helper.dart';
import '../models/work.dart';
import '../widgets/work_item.dart';
import 'add_edit_work_screen.dart';

class WorkListScreen extends StatefulWidget {
  const WorkListScreen({super.key});

  @override
  State<WorkListScreen> createState() => _WorkListScreenState();
}

class _WorkListScreenState extends State<WorkListScreen> {
  List<AcademicWork> _works = [];
  bool _isLoading = true;
  bool _isRefreshing = false;

  @override
  void initState() {
    super.initState();
    _loadWorks();
  }

  Future<void> _loadWorks() async {
    if (!mounted) return;

    setState(() {
      _isRefreshing = true;
    });

    try {
      final works = await DatabaseHelper.instance.getAllAcademicWorks();

      if (!mounted) return;
      setState(() {
        _works = works;
        _isLoading = false;
        _isRefreshing = false;
      });
    } catch (e) {
      if (!mounted) return;
      setState(() {
        _isLoading = false;
        _isRefreshing = false;
      });
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text('Ошибка загрузки работ: $e'),
          backgroundColor: Colors.red,
        ),
      );
    }
  }

  Future<void> _editWork(AcademicWork work) async {
    final result = await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => AddEditWorkScreen(work: work),
      ),
    );

    if (result == true) {
      await _loadWorks();
    }
  }

  Future<void> _addNewWork() async {
    final result = await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => const AddEditWorkScreen(),
      ),
    );

    if (result == true) {
      await _loadWorks();
    }
  }

  Future<void> _deleteWork(int id) async {
    try {
      await DatabaseHelper.instance.deleteAcademicWork(id);
      await _loadWorks();

      if (!mounted) return;
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(
          content: Text('Работа удалена'),
          duration: Duration(seconds: 2),
        ),
      );
    } catch (e) {
      if (!mounted) return;
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text('Ошибка удаления: $e'),
          backgroundColor: Colors.red,
        ),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Учебные работы'),
        actions: [
          if (_isRefreshing)
            const Padding(
              padding: EdgeInsets.only(right: 16.0),
              child: SizedBox(
                width: 20,
                height: 20,
                child: CircularProgressIndicator(strokeWidth: 2),
              ),
            ),
        ],
      ),
      body: _isLoading
          ? const Center(child: CircularProgressIndicator())
          : _works.isEmpty
          ? Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Icon(Icons.assignment, size: 64, color: Colors.grey),
            const SizedBox(height: 16),
            const Text(
              'Нет учебных работ',
              style: TextStyle(fontSize: 18, color: Colors.grey),
            ),
            const SizedBox(height: 8),
            const Text(
              'Нажмите + чтобы добавить работу',
              style: TextStyle(color: Colors.grey),
            ),
            const SizedBox(height: 16),
            ElevatedButton.icon(
              onPressed: _addNewWork,
              icon: const Icon(Icons.add),
              label: const Text('Добавить работу'),
            ),
          ],
        ),
      )
          : RefreshIndicator(
        onRefresh: _loadWorks,
        child: ListView.builder(
          padding: const EdgeInsets.all(8),
          itemCount: _works.length,
          itemBuilder: (context, index) {
            final work = _works[index];
            return WorkItem(
              work: work,
              onEdit: () => _editWork(work),
              onDelete: () => _deleteWork(work.id),
            );
          },
        ),
      ),
      floatingActionButton: _works.isEmpty
          ? null
          : FloatingActionButton(
        onPressed: _addNewWork,
        child: const Icon(Icons.add),
      ),
    );
  }
}