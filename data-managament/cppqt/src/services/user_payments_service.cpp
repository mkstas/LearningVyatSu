#include "user_payments_service.h"

UserPaymentsService::UserPaymentsService(Database &db) : _db(db) {}

std::vector<UserPayment> UserPaymentsService::getAll()
{
    std::vector<UserPayment> user_payments;

    try
    {
        pqxx::result result = _db.execute(
            "SELECT up.id, u.phone_number, p.title, up.card_number, up.cvv "
            "FROM user_payments up "
                "JOIN users u ON u.id = up.user_id "
                "JOIN payments p ON p.id = up.payment_id"
        );

        for (const auto& row : result) {
            UserPayment user_payment;

            user_payment.id = row[0].as<int>();
            user_payment.phone_number = row[1].as<std::string>();
            user_payment.title = row[2].as<std::string>();
            user_payment.card_number = row[3].as<std::string>();
            user_payment.cvv = row[4].as<std::string>();

            user_payments.push_back(user_payment);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Get all user payments error: " << e.what() << std::endl;
    }

    return user_payments;
}

std::vector<UserPayment> UserPaymentsService::getBySearch(const std::string substring)
{
    std::vector<UserPayment> user_payments;

    try
    {
        pqxx::result result = _db.execute(
            "SELECT up.id, u.phone_number, p.title, up.card_number, up.cvv "
            "FROM user_payments up "
                "JOIN users u ON u.id = up.user_id "
                "JOIN payments p ON p.id = up.payment_id "
            "WHERE up.card_number LIKE '%" + substring + "%'"
        );

        for (const auto& row : result) {
            UserPayment user_payment;

            user_payment.id = row[0].as<int>();
            user_payment.phone_number = row[1].as<std::string>();
            user_payment.title = row[2].as<std::string>();
            user_payment.card_number = row[3].as<std::string>();
            user_payment.cvv = row[4].as<std::string>();

            user_payments.push_back(user_payment);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Get user payments by search error: " << e.what() << std::endl;
    }

    return user_payments;
}

bool UserPaymentsService::create(UserPaymentDto dto)
{
    try
    {
        _db.execute(
            std::format(
                "SELECT create_user_payment({}, {}, '{}', '{}')",
                dto.user_id, dto.payment_id, dto.card_number, dto.cvv
            )
        );

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Create user payments error: " << e.what() << std::endl;

        return false;
    }
}

bool UserPaymentsService::update(int id, UserPaymentDto dto)
{
    try
    {
        _db.execute(
            std::format(
                "SELECT update_user_payment({}, {}, {}, '{}', '{}')",
                id, dto.user_id, dto.payment_id, dto.card_number, dto.cvv
            )
        );

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Update user payments error: " << e.what() << std::endl;

        return false;
    }
}

bool UserPaymentsService::remove(int id)
{
    try
    {
        _db.execute(
            std::format(
                "DELETE FROM user_payments WHERE id = {}", id
            )
        );

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Delete user payments error: " << e.what() << std::endl;

        return false;
    }
}
