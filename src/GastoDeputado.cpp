#include "../headers/libraries.h"

GastoDeputado::GastoDeputado() {}

GastoDeputado::GastoDeputado(
        int gasto_id,
        string buggedDate,
        string receiptDate,
        int deputyId,
        string politicalParty,
        string stateCode,
        string deputyName,
        string receiptSocialSecurityNumber,
        string receiptDescription,
        string establishmentName,
        int receiptValue) {
    this->gasto_id = gasto_id;
    this->buggedDate = buggedDate;
    this->receiptDate = receiptDate;
    this->deputyId = deputyId;
    this->politicalParty = politicalParty;
    this->stateCode = stateCode;
    this->deputyName = deputyName;
    this->receiptSocialSecurityNumber = receiptSocialSecurityNumber;
    this->receiptDescription = receiptDescription;
    this->establishmentName = establishmentName;
    this->receiptValue = receiptValue;
}

GastoDeputado::~GastoDeputado() {}

int GastoDeputado::getGastoId() {
    return this->gasto_id;
}

void GastoDeputado::setGastoId(int gasto_id) {
    this->gasto_id = gasto_id;
}

string GastoDeputado::getBuggedDate() {
    return this->buggedDate;
}

void GastoDeputado::setBuggedDate(string buggedDate) {
    this->buggedDate = buggedDate;
}

string GastoDeputado::getReceiptDate() {
    return this->receiptDate;
}

void GastoDeputado::setReceiptDate(string receiptDate) {
    this->receiptDate = receiptDate;
}

int GastoDeputado::getDeputyId() {
    return this->deputyId;
}

void GastoDeputado::setDeputyId(int deputyId) {
    this->deputyId = deputyId;
}

string GastoDeputado::getPoliticalParty() {
    return this->politicalParty;
}

void GastoDeputado::setPoliticalParty(string politicalParty) {
    this->politicalParty = politicalParty;
}

string GastoDeputado::getStateCode() {
    return this->stateCode;
}

void GastoDeputado::setStateCode(string stateCode) {
    this->stateCode = stateCode;
}

string GastoDeputado::getDeputyName() {
    return this->deputyName;
}

void GastoDeputado::setDeputyName(string deputyName) {
    this->deputyName = deputyName;
}

string GastoDeputado::getReceiptSocialSecurityNumber() {
    return this->receiptSocialSecurityNumber;
}

void GastoDeputado::setReceiptSocialSecurityNumber(string receiptSocialSecurityNumber) {
    this->receiptSocialSecurityNumber = receiptSocialSecurityNumber;
}

string GastoDeputado::getReceiptDescription() {
    return receiptDescription;
}

void GastoDeputado::setReceiptDescription(string receiptDescription) {
    this->receiptDescription = receiptDescription;
}

string GastoDeputado::getEstablishmentName() {
    return establishmentName;
}

void GastoDeputado::setEstablishmentName(string establishmentName) {
    this->establishmentName = establishmentName;
}

int GastoDeputado::getReceiptValue() {
    return receiptValue;
}

void GastoDeputado::setReceiptValue(int receiptValue) {
    this->receiptValue = receiptValue;
}
