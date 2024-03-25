#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool check_digits(string s) {
    bool flag = true;
    for (int i = 0; i < s.size(); i++) {
        if (!isdigit(s[i])) {
            flag = false;
            break;
        }
    }
    return flag;
}

bool check_state(string s, int count_of_state) {
    string str;
    int counter = 0;
    for (int i = 1; i < s.size(); i++) { // проверяем индекс введенной вершины
        str += s[i];
        if (isdigit(s[i])) counter++;
    }
    if (counter != str.size()) { // если количество символов (цифр) меньше чем (не равно) размеру строки 
        return false;
    }
    else {
        if (s[0] != 'q' || stoi(str) >= count_of_state) {
            return false;
        }
        else {
            return true;
        }
    }
}

bool check_wasnt(string s, char symb) {
    bool flag = true;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == symb) {
            flag = false;
            break;
        }
    }
    return flag;
}

void remove(vector<string>& v){
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = remove(it + 1, end, *it);
    }
    v.erase(end, v.end());
}

string f_vec_to_str(vector<string> v) {
    string s;
    for (int i = 0; i < v.size(); i++) {
        s += v[i];
    }
    return s;
}

string just_once(string s) {
    if (s.size() <= 1) return s;
    else {
        string result;  //s - начальная строка, result - конечная
        char prev;   // последний неповторяющийся символ, который мы встретили
        prev = s[0];
        result += s[0];
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != prev) {
                prev = s[i];
                result += s[i];
            }
        }
        return result;
    }
}
void rec_3(int i, int j, int eps, int** arr, vector<string>& str, vector<string> alph, bool was_symb) {
    if (arr[i][j] != -1 || arr[i][eps] != -1) {
        if (arr[i][j] != -1) {
            if (was_symb) {
                str.push_back(to_string(arr[i][j]));
                rec_3(arr[i][j], j, eps, arr, str, alph, false);
            }
            else {
                str.push_back(to_string(arr[i][j]));
            }
        }
        if (arr[i][eps] != -1) {
            if (was_symb) rec_3(arr[i][eps], j, eps, arr, str, alph, true);
            else {
                str.push_back(to_string(arr[i][eps]));
                rec_3(arr[i][eps], j, eps, arr, str, alph, false);
            }
        }
    }
    else {
        return;
    }
}

bool checkword(string s, vector<string>alphabet) {
    bool flag = true;
    for (int i = 0; i < s.size(); i++) {
        int count = 0;
        for (int j = 0; j < alphabet.size() - 1; j++) {
            string symb;
            symb += s[i];
            if (symb == alphabet[j]) {
                count = 1;
                break;
            }
            symb = "";
        }
        if (count == 0) {
            flag = false;
            break;
        }
    }
    return flag;
}

int main() {
    setlocale(LC_ALL, "rus");
    ////ALPHABET
    cout << "ВВОД АЛФАВИТА\n";
    cout << "Введите алфавит: " << endl;
    vector<string> alphabet;
    int counter = 1;
    while (true) {
        string symbol;
        cout << counter << ". ";
        getline(cin, symbol);
        if (symbol == "end") break;
        while (symbol.size() != 1 || symbol == "e") {
            cout << "Ошибка. Введите символ: " << endl << counter << ". ";
            getline(cin, symbol);
            if (symbol == "end") break;
        }
        if (symbol == "end") break;
        alphabet.push_back(symbol);
        counter++;
    }
    alphabet.push_back("e");

    //STATES
    cout << endl << "\nВВОД КОЛИЧЕСТВА СОСТОЯНИЙ\n";
    counter = 0;
    vector<int> count_of_states;
    string str_count_states;
    cout << "Введите количество состояний не равное нулю: " << endl;
    getline(cin, str_count_states);
    while (!check_digits(str_count_states) || str_count_states == "0" || str_count_states.size() == 0) {
        cout << "Ошибка. Введите количество состояний не равное нулю: ";
        getline(cin, str_count_states);
    }
    int ct_sts = stoi(str_count_states);
    for (int i = 0; i < ct_sts; i++) {
        int state = i;
        count_of_states.push_back(state);
    }

    //START STATES
    cout << endl << "\nВВОД НАЧАЛЬНЫХ СОСТОЯНИЙ\n";
    string start_states;
    string str_start_state;
    cout << "Введите начальное состояние (qi): "<< endl;
    getline(cin, str_start_state);
    if (str_start_state == "end" && start_states.size() > 0);
    while (!check_state(str_start_state, ct_sts) || str_start_state.size() <= 1) {
        cout << "Ошибка. Введите начальные состояния (qi) и меньше чем: " << endl;
        getline(cin, str_start_state);
    }
    start_states = str_start_state;

    ////FINAL STATES
    cout << endl << "\nВВОД ФИНАЛЬНЫХ СОСТОЯНИЙ\n";
    vector<string> final_states;
    string str_final_state;
    cout << "Введите финальную вершину (qi): " << endl;
    getline(cin, str_final_state);
    while (!check_state(str_final_state, ct_sts) || str_final_state.size() <= 1 || str_final_state == start_states) {
        cout << "Ошибка. Введите финальную вершину (qi) меньше чем " << ct_sts - counter << ":" << endl;
        getline(cin, str_final_state);
    }
    final_states.push_back(str_final_state);


    //TABLE Qi
    //cout << "\nВВОД ТАБЛИЦЫ Qi\n";
    vector<int> q_table;
    //vector<string> yes= {"q3", "", "q1", "q3", "q2", "", "q2", "", "", "", "q3", "q2"};
    for (int i = 0; i < count_of_states.size(); i++) {
        cout << "Для вершины q" << i << ": " << endl;
        for (int j = 0; j < alphabet.size(); j++) {
            string str_edges;
            int cou = 0;
            while (cou != 1) {
                string vertex;
                cout << "Введите куда можно попасть из вершины q" << i << " по сигналу " << alphabet[j] << ": ";
                getline(cin, vertex);
                if (vertex.size() == 0) break;
                while (!check_state(vertex, ct_sts)) {
                    cout << "Ошибка. Введите куда можно попасть из вершины q" << i << " по сигналу " << alphabet[j] << ": ";
                    getline(cin, str_edges);
                    if (vertex.size() == 0) break;
                }
                if (vertex.size() == 0) break;
                str_edges += vertex;
                cou++;
            }
            if(str_edges.size() != 0) q_table.push_back((int)str_edges[1] - 48);
            else q_table.push_back(-1);
            cout << "\n";
        }
        cout << "\n";
    }

    ////TEST
    //for (int i = 0; i < yes.size(); i++) {
    //    if (yes[i].size() != 0) q_table.push_back((int)((yes[i])[1]) - 48);
    //    else q_table.push_back(-1);
    //}
    

    //Q-ТАБЛИЦА
    for (int i = 0; i < alphabet.size(); i++) {
        if (i == 0)cout << "\t" << alphabet[i];
        else cout << "\t" << alphabet[i];
    }
    cout << "\n";
    int cn = 0;
    for (int i = 0; i < q_table.size(); i++) {
        if (i % alphabet.size() == 0 && q_table[i] != -1) {
            cout << "q" << cn << "|\t" << "q" << q_table[i] << "\t";
            cn++;
        }
        else if (i % alphabet.size() == 0 && q_table[i] == -1) {
            cout << "q" << cn << "|\t" << q_table[i] << "\t";
            cn++;
        }
        else if ((i + 1) % alphabet.size() == 0 && q_table[i] != -1) cout << "q" << q_table[i] << endl;
        else if ((i + 1) % alphabet.size() == 0 && q_table[i] == -1) cout << q_table[i] << endl;
        else if (q_table[i] == -1) cout << q_table[i] << '\t';
        else cout << "q" << q_table[i] << "\t";
    }
    int c = 0;
    int** arr = new int* [count_of_states.size()];
    for (int i = 0; i < count_of_states.size(); i++) {
        arr[i] = new int[alphabet.size()];
        for (int j = 0; j < alphabet.size(); j++) {
            arr[i][j] = q_table[c];
            c++;
        }
    }

    //EPSILON ЗАМЫКАНИЯ
    vector<string>epsilon_closes;
    for (int i = 0; i < count_of_states.size(); i++) {
        vector<string>exp;
        bool flag_1 = true;
        string eps_cl = to_string(i);
        int j = i;
        int cat = 0;
        do {
            if (!check_wasnt(eps_cl, char(j)) || cat == 0){
                if (arr[j][alphabet.size() - 1] == -1) {
                    flag_1 = false;
                    break;
                }
                else {
                    j = arr[j][alphabet.size() - 1];
                    eps_cl += to_string(j);
                    cat = 1;
                }
            }
            else {
                break;
            }
        } while (flag_1);
        epsilon_closes.push_back(just_once(eps_cl));
    }
    cout << endl;
    for (int i = 0; i < count_of_states.size(); i++) {
        string s_e = epsilon_closes[i];
        cout << "s[" << i << "] = ";
        for (int j = 0; j < s_e.size(); j++) {
            cout << s_e[j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl<< "ЭПСИЛОН ЗАМЫКАНИЯ: " << endl;
    for (int i = 0; i < epsilon_closes.size(); i++) {
        string s_epps = epsilon_closes[i];
        cout << "s" << i << "{";
        for (int j = 0; j < s_epps.size(); j++) {
            if (j != s_epps.size() - 1) cout << "q" << s_epps[j] << ",";
            else cout << "q" << s_epps[j] << "}";
        }
        cout << '\n';
    }
    cout << endl;

    //Начальные s
    vector<string> s_starts;
    s_starts.push_back("0");
    string starts_with_eps;
    starts_with_eps = epsilon_closes[0];
    for (int i = 1; i < epsilon_closes.size(); i++) {
        string s = epsilon_closes[i];
        bool flag = true;
        for (int j = 0; j < s.size(); j++) {
            for (int k = 0; k < starts_with_eps.size(); k++) {
                if (s[j] == starts_with_eps[k]) {
                    flag = false;
                    s_starts.push_back(to_string(i));
                    break;
                }
            }
            if (!flag) break;
        }
    }
    remove(s_starts);
    cout << endl << "НАЧАЛЬНЫЕ S" << endl;
    for (int i = 0; i < s_starts.size(); i++) {
        if (i != s_starts.size() - 1)cout << "s" << s_starts[i] << ", ";
        else cout << "s" << s_starts[i] << endl;
    }
    cout << endl;

    //Финальные s
    vector<string> s_finals;
    string f_state = final_states[0];
    string f_vert = epsilon_closes[stoi(to_string(f_state[1])) - 48];
    s_finals.push_back(to_string(f_state[1] - 48));
    for (int i = 0; i < epsilon_closes.size(); i++) {
        string s = epsilon_closes[i];
        bool flag = true;
        for (int j = 0; j < s.size(); j++) {
            for (int k = 0; k < f_vert.size(); k++) {
                if (to_string(s[j]) == to_string(f_vert[k])) {
                    flag = false;
                    s_finals.push_back(to_string(i));
                    break;
                }
            }
            if (!flag) break;
        }
    }
    remove(s_finals);
    cout << endl << "ФИНАЛЬНЫЕ S" << endl;
    for (int i = 0; i < s_finals.size(); i++) {
        if (i != s_finals.size() - 1)cout << "s" << s_finals[i] << ", ";
        else cout << "s" << s_finals[i] << endl;
    }
    cout << endl;

    //пути достижения вершины по букве+эпсилону
    vector<vector<string>> matrix(count_of_states.size(), vector<string>(alphabet.size() - 1));
    for (int i = 0; i < count_of_states.size(); i++) {
        for (int j = 0; j < alphabet.size() - 1; j++) {
            vector<string> str;
            string word;
            rec_3(i, j, alphabet.size() - 1, arr, str, alphabet, true);
            remove(str);
            word = f_vec_to_str(str);
            matrix[i][j] = (word);
        }
    }
    
    //все возможные пути для каждого замыкания по буквам
    vector<vector<string>>all_rutes(count_of_states.size(), vector<string>(alphabet.size() - 1));
    int new_counter = 0;
    while (new_counter != epsilon_closes.size()) {
        string s = epsilon_closes[new_counter];//берем s из ЭпсЗам  
        for (int symb = 0; symb < alphabet.size() - 1; symb++) {
            vector<string> rute;
            for (int i = 0; i < s.size(); i++) {
                int a = (int)s[i] - 48;
                rute.push_back(matrix[a][symb]);
            }
            remove(rute);
            string rr = f_vec_to_str(rute);
            all_rutes[new_counter][symb] = rr;
        }
        new_counter++;
    }

    vector<vector<string>> s_table(count_of_states.size(), vector<string>(alphabet.size() - 1));
    for (int symb = 0; symb < alphabet.size() - 1; symb++) {
        for (int i = 0; i < count_of_states.size(); i++) {
            string rute = all_rutes[i][symb];
            string real_s;
            for (int s = 0; s < epsilon_closes.size(); s++) {
                int counter_inner = 0;
                string s_from_eps = epsilon_closes[s];
                for (int k = 0; k < rute.size(); k++) {
                    for (int j = 0; j < s_from_eps.size(); j++) {
                        if (s_from_eps[j] == rute[k]) counter_inner++;
                    }
                }
                if (counter_inner == s_from_eps.size()) real_s += to_string(s);
            }
            if (real_s != "") s_table[i][symb] = real_s;
            else s_table[i][symb] = "-1";
        }
    }
    cout << endl;

    //S-ТАБЛИЦА
    cout << "S-ТАБЛИЦА:" << endl;
    for (int i = 0; i < alphabet.size() - 1; i++) {
        if (i == 0)cout << "\t" << alphabet[i];
        else cout << "\t" << alphabet[i];
    }
    cout << endl;
    for (int i = 0; i < count_of_states.size(); i++) {
        cout << "s" << i << "|\t";
        for (int j = 0; j < alphabet.size() - 1; j++) {
            if (s_table[i][j] != "-1") {
                string s_epss = s_table[i][j];
                for (int k = 0; k < s_epss.size(); k++) {
                    cout << "s" << s_epss[k];
                }
                cout << '\t';
            }
            else {
                cout << "-1\t";
            }
        }
        cout << endl;
    }
    vector<string> p_list;

    //нахождение р0
    string p0;
    for (int i = 0; i < count_of_states.size(); i++) {
        string s_eps = epsilon_closes[i];
        bool fl = false;
        for (int j = 0; j < s_eps.size(); j++) {
            for (int k = 0; k < epsilon_closes[0].size(); k++) {
                string nn = epsilon_closes[0];
                if (s_eps[j] == nn[k]) {
                    fl = true;
                }
            }
            if (fl) {
                p0 += to_string(i);
                break;
            }
        }
    }
    p_list.push_back(p0);
    cout << endl;

    //нахождение остальных р
    for (int i = 0; i < count_of_states.size(); i++) {
        for (int j = 0; j < alphabet.size() - 1; j++) {
            if (s_table[i][j] != "-1") {
                p_list.push_back(s_table[i][j]);
            }
        }
    }
    remove(p_list);
    vector<string> p_table;
    for (int i = 0; i < p_list.size(); i++) {
        string s_sepss = p_list[i];
        for (int j = 0; j < alphabet.size() - 1; j++) {
            vector<string> ob;
            for (int k = 0; k < s_sepss.size(); k++) {
                if (s_table[(int)s_sepss[k] - 48][j] != "-1") {
                    ob.push_back(s_table[(int)s_sepss[k] - 48][j]);
                }
            }
            remove(ob);
            string sstr = f_vec_to_str(ob);
            if(sstr.size() == 0) p_table.push_back("-1");
            else p_table.push_back(sstr);
        }
    }
    vector<vector<string>> last_table(p_list.size(), vector<string>(alphabet.size() - 1));
    int counterr = 0;
    for (int i = 0; i < p_list.size(); i++) {
        for (int j = 0; j < alphabet.size() - 1; j++) {
            if (p_table[counterr] != "-1") {
                last_table[i][j] = p_table[counterr];
                counterr++;
            }
            else {
                last_table[i][j] = "-1";
                counterr++;
            }
        }
    }
    vector<vector<string>> last_p_table(p_list.size(), vector<string>(alphabet.size() - 1));
    for (int i = 0; i < p_list.size(); i++) {
        for (int j = 0; j < alphabet.size() - 1; j++) {
            for (int k = 0; k < p_list.size(); k++) {
                if (p_list[k] == last_table[i][j]) {
                    last_p_table[i][j] = to_string(k);
                    break;
                }
                if (last_table[i][j] == "-1") {
                    last_p_table[i][j] = "-1";
                    break;
                }
            }
        }
    }
    cout << endl << "P-ТАБЛИЦА" << endl << "\t";
    for (int i = 0; i < alphabet.size() - 1; i++) {
        cout << alphabet[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < p_list.size(); i++){
        cout << "p" << i  << "|" << "\t";
        for (int j = 0; j < alphabet.size() - 1; j++) {
            if (last_p_table[i][j] != "-1") {
                if ((j + 1) % (alphabet.size() - 1) != 0) cout << "p" << last_p_table[i][j] << "\t";
                else cout << "p" << last_p_table[i][j] << endl;
            }
            else {
                if ((j + 1) % (alphabet.size() - 1) != 0) cout << last_p_table[i][j] << "\t";
                else cout << last_p_table[i][j] << endl;
            }
        }
    }
    cout << endl;

    //НАЧАЛЬНЫЕ Р
    vector<string> p_starts;
    p_starts.push_back("0");
    for (int i = 0; i < p_list.size(); i++) {
        string p = p_list[i];
        bool flag = true;
        for (int j = 0; j < p.size(); j++) {
            for (int k = 0; k < s_starts.size(); k++) {
                if (s_starts[k] == to_string(p[j] - 48)) {
                    flag = false;
                    p_starts.push_back(to_string(i));
                    break;
                }
            }
            if (!flag) break;
        }
    }
    remove(p_starts);
    cout << endl << "НАЧАЛЬНЫЕ Р:" << endl;
    for (int i = 0; i < p_starts.size(); i++) {
        if (i != p_starts.size() - 1) cout << "p" << p_starts[i] << ", ";
        else cout << "p" << p_starts[i] << endl;
    }

    //ФИНАЛЬНЫЕ Р
    vector<string> p_finals;
    for (int i = 0; i < p_list.size(); i++) {
        string p = p_list[i];
        bool flag = true;
        for (int j = 0; j < p.size(); j++) {
            for (int k = 0; k < s_finals.size(); k++) {
                if (s_finals[k] == to_string(p[j] - 48)) {
                    flag = false;
                    p_finals.push_back(to_string(i));
                    break;
                }
            }
            if (!flag) break;
        }
    }
    remove(p_finals);
    cout << endl << "ФИНАЛЬНЫЕ Р:" << endl;
    for (int i = 0; i < p_finals.size(); i++) {
        if (i != p_finals.size() - 1) cout << "p" << p_finals[i] << ", ";
        else cout << "p" << p_finals[i] << endl;
    }
    cout << endl;

    //ВВОД СЛОВА
    while (true) {
        string word;
        cout << "Введите слово: ";
        getline(cin, word);
        while (!checkword(word, alphabet)) {
            cout << "Ошибка. Введите слово правильно: ";
            getline(cin, word);
        }

        //ПРОВЕРКА СЛОВА ДЛЯ ГРАФА
        int row = -1;
        int col = -1;
        bool flag_word = true;
        for (int i = 0; i < word.size(); i++) {
            if (i == 0) {
                string symb;
                symb += word[i];
                for (int j = 0; j < alphabet.size() - 1; j++) {
                    if (symb == alphabet[j]) {
                        col = j;
                        break;
                    }
                }
                if (last_p_table[0][col] != "-1" && i != word.size() - 1) {
                    cout << "(p0, " << word << ") -> ";
                    row = stoi(last_p_table[0][col]);
                }
                else if (last_p_table[0][col] != "-1" && word.size() == 1) {
                    cout << "(p0, " << word << ") -> (p" << last_p_table[0][col] << ", e)";
                    row = stoi(last_p_table[0][col]);
                }
                else {
                    cout << "(p" << row << ", " << word << ") -> " << "Ошибка! Проходит через несуществующий путь" << endl;
                    flag_word = false;
                    break;
                }
            }
            else if (i != 0 && i != word.size() - 1) {
                string symb;
                symb += word[i];
                string new_word;
                for (int k = i; k < word.size(); k++) {
                    new_word += word[k];
                }
                int col;
                for (int j = 0; j < alphabet.size() - 1; j++) {
                    if (symb == alphabet[j]) {
                        col = j;
                        break;
                    }
                }
                if (last_p_table[row][col] != "-1") {
                    cout << "(p" << row << ", " << new_word << ") -> ";
                    row = stoi(last_p_table[row][col]);
                }
                else {
                    cout << "(p" << row << ", " << new_word << ") -> " << "Ошибка! Проходит через несуществующий путь" << endl;
                    flag_word = false;
                    break;
                }
            }
            else {
                string symb;
                symb += word[i];
                string new_word;
                for (int k = i; k < word.size(); k++) {
                    new_word += word[k];
                }
                int col;
                for (int j = 0; j < alphabet.size() - 1; j++) {
                    if (symb == alphabet[j]) {
                        col = j;
                        break;
                    }
                }
                if (last_p_table[row][col] != "-1") {
                    cout << "(p" << row << ", " << new_word << ") -> " << "(p" << last_p_table[row][col] << ", e)";
                    row = stoi(last_p_table[row][col]);
                }
                else {
                    cout << "(p" << row << ", " << new_word << ") -> " << "Ошибка! Проходит через несуществующий путь" << endl;
                    flag_word = false;
                    break;
                }
            }
        }
        cout << endl;
        if (!flag_word) {
            cout << endl << "Неверное слово" << endl;
        }
        else {
            bool flg = false;
            for (int i = 0; i < p_finals.size(); i++) {
                if (stoi(p_finals[i]) == row) {
                    cout << endl << "Слово подходит" << endl;
                    flg = true;
                    break;
                }
            }
            if (!flg) cout << endl << "Неверное слово" << endl;
        }
    }

    for (int i = 0; i < count_of_states.size(); i++) {
        delete[] arr[i];
    }
    delete[] arr;
}