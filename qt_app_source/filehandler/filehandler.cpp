#include "filehandler.h"
#include <iostream>
#include <cstdlib>
#include <QFileInfo>
#include <QMimeDatabase>

void FileHandler::openFile(const QString &path) {
  this->file.open(path.toStdString());
  this->name_of_current_file = QString(QFileInfo(path).fileName()).toStdString();
  this->extension_of_current_file = QString(QFileInfo(path).completeSuffix()).toStdString();
}

bool FileHandler::isFileOpen() {
  return this->file.is_open();
}

// убрать кучу перегрузок функции, добавить перегрузку преобразования данных также надо походу добавить
// скип хештегов
void FileHandler::readDataField(int &field) {
  std::string line;
  while (getline(this->file, line)) {
    if (line[0]=='#') {
      continue;
    }
    else{
      break;
    }
  }
  field = std::atoi(line.c_str());
}

void FileHandler::readDataField(double &field) {
  std::string line;
  while (getline(this->file, line)) {
    if (line[0]=='#') {
      continue;
    }
    else{
      break;
    }
  }
  field = std::atof(line.c_str());
}

void FileHandler::readDataField(std::string &field) {
  std::string line;
  while (getline(this->file, line)){
    if (line[0] == '#') {
      continue;
    }
    else{
      break;
    }
  }
  field = line;
}

void FileHandler::readDataField(std::vector<std::string> &field) {
  std::string line;
  while (getline(this->file, line)){
    if (line[0] == '#') {
      continue;
    }
    else{
      break;
    }
  }
  std::string name;
  for ( auto symbol: line ){
    if ( symbol == ';' ){
      field.push_back(name);
      name.clear();
    }
    else{
      name += symbol;
    }
  }
  if (!name.empty() && name != ";" && name != " " && (int)name[0] != 13) field.push_back(name);
}

void FileHandler::readDataField(std::vector<CanalOfSignal> &field, const std::vector<std::string> &names) {
  std::string line;
  for ( const auto& name: names ){
    field.push_back(CanalOfSignal(name, this->name_of_current_file));
  }

  while ( getline( this->file, line ) ){
    if (line[0] == '#') {
      continue;
    }
    std::string string_num;
    int name_index = 0;
    for ( auto sym: line ){
        if ( sym == ' ' ){
          field[name_index % field.size()].values_of_signal.push_back(atof(string_num.c_str()));
          name_index++;
          string_num.clear();
          continue;
        }
        string_num += sym;
    }
    if (!string_num.empty()){
      field[name_index % field.size()].values_of_signal.push_back(atof(string_num.c_str()));
    }
  }
}
//работает только для двух расширений, нужно убрать громоздкие условия и переделать, чтобы преобразование
// данных шло сначала, а потом перетекала в единый метод считывания либо сделать два отдельных метода под
// каждое расширение, да и вообще хендлер надо переделать, работа с cvs написана ужасно топорно.
// да и вообще когда я вернулся сюда, увидел что память утекает как вода

void FileHandler::readNamesOfChannelFromCVS(){

}

dataStructure* FileHandler::getData() {

    if ( this->extension_of_current_file == "csv" ){
        dataStructure *structured_data;
        structured_data = new dataStructure;
        if ( this->isFileOpen() ){
            std::string line;
            getline(this->file, line);
            std::string current_name;
            std::vector<std::string> name_of_columns;
            for ( auto sym: line ){
                if ( sym == '"' ){
                    continue;
                }
                if ( sym == ',' ){
                    name_of_columns.push_back(current_name);
                    current_name = "";
                    continue;
                }
                current_name += sym;
            }

            for (unsigned int i = 1; i < name_of_columns.size(); i++ ){
                structured_data->channels_names.push_back(name_of_columns[i]);
                structured_data->signals_channels.push_back(CanalOfSignal(name_of_columns[i], this->name_of_current_file));
            }


            std::vector<float> time_values;
            while ( getline(this->file, line) ){
                int cnt_on_channels = 0;
                bool is_time = true;
                std::string current_num = "";
                for ( auto sym: line ){
                    if ( sym == ',' ){
                        if ( is_time ){
                            time_values.push_back(atof(current_num.c_str()));
                            is_time = false;
                            current_num = "";
                            continue;
                        }
                        else{
                            structured_data->signals_channels[cnt_on_channels].values_of_signal.push_back(atof(current_num.c_str()));
                            current_num = "";
                            cnt_on_channels++;
                            continue;
                        }
                    }
                    current_num += sym;
                }
            }

            structured_data->number_of_channels = structured_data->signals_channels.size();
            structured_data->number_of_samples = structured_data->signals_channels.back().values_of_signal.size();
            structured_data->signal_start_date = "unknown";
            structured_data->signal_start_time = "unknown";
            structured_data->recording_duration = time_values.back() - time_values[0];
            structured_data->period_of_tick = double((double)structured_data->recording_duration / (double)structured_data->number_of_samples);
            structured_data->sampling_frequency = 1.0 / structured_data->period_of_tick;
            for ( auto &channel: structured_data->signals_channels ){
                channel.number_of_samples = structured_data->number_of_samples;
                channel.period_of_tick = structured_data->period_of_tick;
                channel.sampling_frequency = structured_data->sampling_frequency;
                channel.recording_duration = structured_data->recording_duration;
            }
            return structured_data;
        }
    }

    if ( this->extension_of_current_file == "txt" ){
    dataStructure *structured_data;
    structured_data = new dataStructure;
    if (this->isFileOpen()){
      this->readDataField(structured_data->number_of_channels);
      this->readDataField(structured_data->number_of_samples);
      this->readDataField(structured_data->sampling_frequency);
      this->readDataField(structured_data->signal_start_date);
      this->readDataField(structured_data->signal_start_time);
      this->readDataField(structured_data->channels_names);

      this->readDataField(structured_data->signals_channels, structured_data->channels_names);
      structured_data->period_of_tick = ( 1 / structured_data->sampling_frequency);
      structured_data->recording_duration = ( 1 / structured_data->sampling_frequency) * structured_data->number_of_samples;

      //цикл дополняющий каналы сигналов, через риддатафилд не прочитать, т.к нужно обращаться к structured data, а из
      //риддатафилд доступа не имеем.
      for ( auto &canal: structured_data->signals_channels ){
          canal.number_of_samples = structured_data->number_of_samples;
          canal.period_of_tick = structured_data->period_of_tick;
          canal.sampling_frequency = structured_data->sampling_frequency;
          canal.recording_duration = structured_data->recording_duration;
      }
    }
    return structured_data;
    }
}

void FileHandler::saveFile(dataStructure data_for_save, QString path){

    this->file_to_save.open(path.toStdString());
    this->name_of_current_file = QString(QFileInfo(path).fileName()).toStdString();

    this->file_to_save << data_for_save.number_of_channels << std::endl;
    this->file_to_save << data_for_save.number_of_samples << std::endl;
    this->file_to_save << data_for_save.sampling_frequency << std::endl;
    this->file_to_save << data_for_save.signal_start_date << std::endl;
    this->file_to_save << data_for_save.signal_start_time << std::endl;

    for ( auto name: data_for_save.channels_names ){
        this->file_to_save << name << ";";
    }

    this->file_to_save << std::endl;

    for (int i = 0; i < data_for_save.number_of_samples; i++ ){
        for (CanalOfSignal channel: data_for_save.signals_channels ){
            this->file_to_save << channel.values_of_signal[i] << " ";
        }
        this->file_to_save << std::endl;
    }

    this->file_to_save.close();
}
