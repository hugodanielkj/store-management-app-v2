#include "Cliente.h"

Cliente::Cliente() {
  _id = -1;
}

Cliente::Cliente(std::string nome, std::string telefone, std::string email)
  : _nome(nome), _telefone(telefone), _email(email) {
  _id = -1;
}

int Cliente::getID() const {
  return _id;
}

void Cliente::setID(int id) {
  _id = id;
}

std::string Cliente::getNome() const {
  return _nome;
}

void Cliente::setNome(std::string nome) {
  _nome = nome;
}

std::string Cliente::getTelefone() const {
  return _telefone;
}

void Cliente::setTelefone(std::string telefone) {
  _telefone = telefone;
}

std::string Cliente::getEmail() const {
  return _email;
}

void Cliente::setEmail(std::string email) {
  _email = email;
}
