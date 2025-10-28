#include "payments_service.h"

PaymentsService::PaymentsService(Database &db) : _db(db) {}

std::vector<Payment> PaymentsService::getAll()
{
    std::vector<Payment> payments;

    try
    {
        pqxx::result result = _db.execute("SELECT * FROM payments");

        for (const auto& row : result) {
            Payment payment;

            payment.id = row[0].as<int>();
            payment.title = row[1].as<std::string>();

            payments.push_back(payment);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Get all payments error: " << e.what() << std::endl;
    }

    return payments;
}
