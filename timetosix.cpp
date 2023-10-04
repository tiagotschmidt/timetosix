#include <cstdlib>
#include <cstring>
#include <iostream>
#include <tuple>

#define MAX_WORK_TIME_MINUTES 6 * 60

std::tuple<const char *, const char *>
parse_argument_into_tokens(char *first_real_argument) {
  const char *first_token = std::strtok(first_real_argument, ":");

  const char *second_token = std::strtok(NULL, ":");

  return std::make_tuple(first_token, second_token);
}

int const_char_minutes_to_integer_minutes(const char *string_value) {
  if (string_value != NULL) {
    return atoi(string_value);
  } else {
    std::cout << "NULL value sendo processado!"
              << "\n";
    return 0;
  }
}

int const_char_hours_to_integer_minutes(const char *string_value) {
  if (string_value != NULL) {
    return 60 * atoi(string_value);
  } else {
    std::cout << "NULL value sendo processado!"
              << "\n";
    return 0;
  }
}

void print_info(int worked_time, int remaining_time, int absolute_leave_time) {
  std::cout << "Trabalhado: " << worked_time / 60 << "h:" << worked_time % 60
            << "m.\n";

  std::cout << "Resta: " << remaining_time / 60 << "h:" << remaining_time % 60
            << "m.\n";

  std::cout << "Deve sair às: " << absolute_leave_time / 60
            << "h:" << absolute_leave_time % 60 << "m.\n";

  if (remaining_time <= 0) {
    std::cout << "CUIDADO: ESTÁGIO É LIMITADO EM 6 HORAS DIÁRIAS"
              << ".\n";
  }
}

int absolute_minutes_from_argument(char *argument) {
  auto [first_token, second_token] = parse_argument_into_tokens(argument);

  int start_hour_in_minutes = const_char_hours_to_integer_minutes(first_token);
  int start_minutes = const_char_minutes_to_integer_minutes(second_token);

  return start_hour_in_minutes + start_minutes;
}

int main(int argc, char *argv[]) {
  int real_arguments = argc - 1;

  if (real_arguments != 3) {
    std::cout
        << "Erro ao processar argumentos. Número incorreto de argumentos: "
        << real_arguments << ".\n";
    return 1;
  }

  char *first_real_argument = argv[1];
  char *second_real_argument = argv[2];
  char *third_real_argument = argv[3];

  int absolute_start = absolute_minutes_from_argument(first_real_argument);
  int absolute_end = absolute_minutes_from_argument(second_real_argument);
  int second_absolute_start =
      absolute_minutes_from_argument(third_real_argument);

  int worked_time_minutes = absolute_end - absolute_start;
  int remaining_time_minutes = MAX_WORK_TIME_MINUTES - worked_time_minutes;
  int absolute_leave = second_absolute_start + remaining_time_minutes;

  print_info(worked_time_minutes, remaining_time_minutes, absolute_leave);

  return 0;
}
