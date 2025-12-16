import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import '../database/database_helper.dart';
import '../models/work.dart';

class AddEditWorkScreen extends StatefulWidget {
  final AcademicWork? work;

  const AddEditWorkScreen({super.key, this.work});

  @override
  State<AddEditWorkScreen> createState() => _AddEditWorkScreenState();
}

class _AddEditWorkScreenState extends State<AddEditWorkScreen> {
  final _formKey = GlobalKey<FormState>();
  final _titleController = TextEditingController();
  final _descriptionController = TextEditingController();

  List<WorkType> _workTypes = [];
  WorkType? _selectedWorkType;
  DateTime _selectedDate = DateTime.now();
  bool _isSaving = false;

  @override
  void initState() {
    super.initState();
    _loadWorkTypes();
    _initForm();
  }

  Future<void> _loadWorkTypes() async {
    final types = await DatabaseHelper.instance.getWorkTypes();
    setState(() {
      _workTypes = types;
      if (widget.work != null && _selectedWorkType == null) {
        _selectedWorkType = _workTypes.firstWhere(
              (type) => type.id == widget.work!.workTypeId,
          orElse: () => _workTypes.first,
        );
      } else if (_selectedWorkType == null && _workTypes.isNotEmpty) {
        _selectedWorkType = _workTypes.first;
      }
    });
  }

  void _initForm() {
    if (widget.work != null) {
      _titleController.text = widget.work!.title;
      _descriptionController.text = widget.work!.description;
      _selectedDate = widget.work!.dueDate;
    }
  }

  Future<void> _selectDate(BuildContext context) async {
    final DateTime? picked = await showDatePicker(
      context: context,
      initialDate: _selectedDate,
      firstDate: DateTime(2000),
      lastDate: DateTime(2100),
      // Убрана настройка локали - она теперь глобальная
    );
    if (picked != null && picked != _selectedDate) {
      setState(() {
        _selectedDate = picked;
      });
    }
  }

  Future<void> _saveWork() async {
    if (!_formKey.currentState!.validate() || _selectedWorkType == null) return;
    if (_isSaving) return;

    setState(() {
      _isSaving = true;
    });

    try {
      final work = AcademicWork(
        id: widget.work?.id ?? 0,
        title: _titleController.text.trim(),
        description: _descriptionController.text.trim(),
        workTypeId: _selectedWorkType!.id,
        dueDate: _selectedDate,
      );

      if (work.id == 0) {
        await DatabaseHelper.instance.insertAcademicWork(work);
      } else {
        await DatabaseHelper.instance.updateAcademicWork(work);
      }

      if (!mounted) return;
      Navigator.pop(context, true);
    } catch (e) {
      if (!mounted) return;
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text('Ошибка сохранения: $e'),
          backgroundColor: Colors.red,
        ),
      );
      setState(() {
        _isSaving = false;
      });
    }
  }

  @override
  void dispose() {
    _titleController.dispose();
    _descriptionController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.work == null ? 'Добавить работу' : 'Редактировать работу'),
        actions: [
          IconButton(
            icon: _isSaving
                ? const SizedBox(
              width: 20,
              height: 20,
              child: CircularProgressIndicator(strokeWidth: 2),
            )
                : const Icon(Icons.save),
            onPressed: _isSaving ? null : _saveWork,
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: ListView(
            children: [
              TextFormField(
                controller: _titleController,
                decoration: const InputDecoration(
                  labelText: 'Название работы',
                  border: OutlineInputBorder(),
                  prefixIcon: Icon(Icons.title),
                ),
                validator: (value) {
                  if (value == null || value.trim().isEmpty) {
                    return 'Введите название работы';
                  }
                  return null;
                },
              ),
              const SizedBox(height: 16),
              DropdownButtonFormField<WorkType>(
                value: _selectedWorkType,
                decoration: const InputDecoration(
                  labelText: 'Тип работы',
                  border: OutlineInputBorder(),
                  prefixIcon: Icon(Icons.category),
                ),
                items: _workTypes.map((WorkType type) {
                  return DropdownMenuItem<WorkType>(
                    value: type,
                    child: Text(type.name),
                  );
                }).toList(),
                onChanged: (WorkType? newValue) {
                  setState(() {
                    _selectedWorkType = newValue;
                  });
                },
                validator: (value) {
                  if (value == null) {
                    return 'Выберите тип работы';
                  }
                  return null;
                },
              ),
              const SizedBox(height: 16),
              InkWell(
                onTap: () => _selectDate(context),
                child: InputDecorator(
                  decoration: const InputDecoration(
                    labelText: 'Дата сдачи',
                    border: OutlineInputBorder(),
                    prefixIcon: Icon(Icons.calendar_today),
                  ),
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    children: [
                      Text(
                        DateFormat('dd.MM.yyyy').format(_selectedDate),
                        style: const TextStyle(fontSize: 16),
                      ),
                      const Icon(Icons.calendar_month),
                    ],
                  ),
                ),
              ),
              const SizedBox(height: 16),
              TextFormField(
                controller: _descriptionController,
                decoration: const InputDecoration(
                  labelText: 'Описание',
                  border: OutlineInputBorder(),
                  alignLabelWithHint: true,
                  prefixIcon: Icon(Icons.description),
                ),
                maxLines: 5,
                validator: (value) {
                  if (value == null || value.trim().isEmpty) {
                    return 'Введите описание работы';
                  }
                  return null;
                },
              ),
              const SizedBox(height: 24),
              ElevatedButton(
                onPressed: _isSaving ? null : _saveWork,
                style: ElevatedButton.styleFrom(
                  minimumSize: const Size(double.infinity, 50),
                ),
                child: _isSaving
                    ? const SizedBox(
                  width: 20,
                  height: 20,
                  child: CircularProgressIndicator(
                    strokeWidth: 2,
                    color: Colors.white,
                  ),
                )
                    : const Text(
                  'Сохранить',
                  style: TextStyle(fontSize: 18),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}