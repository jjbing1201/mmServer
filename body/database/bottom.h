#ifndef _DATA_ACCESS_LAYER_HEADER_H_
#define _DATA_ACCESS_LAYER_HEADER_H_

#include <iostream>
#include <map>
#include <vector>
#include <string.h>
#include <stdlib.h>

class DAL_Bottom
{
private:
    std::string stringtoint(std::string resstring); 

protected:
    /* part of update set variables. */
    std::string updateop(std::map<std::string, std::string> upvar);
    /* part of _and && _or operation. */
    std::string unionop(const std::string &op, std::map<std::string, std::string> opvar);
    /* part of desc && asc operation. */
    std::string appendop(const std::string &op, const std::string &columname, const std::string &sequeue = "_desc");
    /* part of _like operation. */
    std::string appendop(const std::string &op, std::map<std::string, std::string> opvar);
    /* part of a > 1 and b < 2 operation. */
    std::string formatop(const std::string &op, std::map<std::string, std::string> opvar);

public:
    DAL_Bottom();
    ~DAL_Bottom();

public:
    /*
     * @param : tablename : insert table's name
     * @param : count : insert variable's count
     * @param : variables : variables in vector
     * #return : int -> 1 for combine, on error for 0.

     * usage : combine cmd with variable of insert.
     * example : INSERT INTO <TABLENAME> VALUES(a1, a2, a3, ...);
     */
    std::map<int, std::string> insert_Bottom(const std::string & tablename, int count, std::vector<std::string> variables);
    /*
     * @param : tablename : update table's name
     * @param : columnname : update column's name
     * @param : variable : update column value
     * #return : int -> 1 for combine, on error for 0.

     * usage : combine cmd with variable of update. 
     * example : UPDATE <TABLENAME> SET COLUMN=a1; 
     */
    std::map<int, std::string> update_all_Bottom(const std::string & tablename, const std::string & columname, const std::string & variable);
    /*
     * @param : tablename : update table's name
     * @param : columnname : update column's name
     * @param : variable : update column value
     * @param : op : union operation like : and, or, like, none.
     * @param : opvar : union operation variables.

     * usage : combine cmd with variable of update.
     * example : UPDATE <TABLENAME> SET COLUMN=a1 where COLUMNB=a2;
     */
    std::map<int, std::string> update_direct_Bottom(const std::string & tablename, std::map<std::string, std::string> upvar, \
                                                    const std::string & op, std::map<std::string, std::string> opvar);
    /* 
     * @param : tablename : update table's name 
     * #return : int -> 1 for combine, on error for 0.
     
     * usage : delete table's all data
     * example : DELETE FROM <TABLENAME>;
    */
    std::map<int, std::string> delete_all_Bottom(const std::string & tablename);
    /*
     * @param : tablename : delete table's name  
     * @param : op : union operation like : and, or, like, none.
     * @param : opvar : union operation variables.

     * #return : int -> 1 for combine, on error for 0.
     * usage : delete table's with variables
     # example : DELETE FROM <TABLENAME> WHERE COLUMN=a1;
     */
    std::map<int, std::string> delete_direct_Bottom(const std::string & tablename, \
                                                    const std::string & op, std::map<std::string, std::string> opvar);
    /*
     * @param : tablename : selete table's name

     * #return : int -> 1 for combine, on error for 0.
     * example : SELECT * FROM <TABLENAME>; 
     */
     std::map<int, std::string> select_all_Bottom(const std::string & tablename);


    /*
     * @param : tablename : selete table's name
     * @param : op : union operation like : and, or, like, none.
     * @param : opvar : union operation variables.

     * #return : int -> 1 for combine, on error for 0.
     * example : SELECT * FROM <TABLENAME>; 
     */
     std::map<int, std::string> select_direct_Bottom(const std::string & tablename, \
                                                     const std::string & op, std::map<std::string, std::string> opvar);

    std::map<int, std::string> select_direct_Bottom_bycount(\
                        const std::string &tablename, \
                        const std::string & op, \
                        std::map<std::string, std::string> opvar);

    std::map<int, std::string> select_direct_Bottom_asc(const std::string & tablename, \
                             const std::string & op, std::map<std::string, std::string> opvar, \
                             std::string column);

    /*
     * @param : tablename : selete table's name
     * @param : op : union operation like : and, or, like, none.
     * @param : opvar : union operation variables.

     * #return : int -> 1 for combine, on error for 0.
     * example : SELECT * FROM <TABLENAME> where a=1 and b>2; 
     */
    std::map<int, std::string> select_direct_Bottom(const std::string & tablename, \
                                                     const std::string & op, std::map<std::string, std::string> opvar, \
                                                     const std::string & otherop, std::map<std::string, std::string> other_opvar);

    std::map<int, std::string> select_direct_Bottom_order(
                            const std::string & tablename, \
                            const std::string & op, \
                            std::map<std::string, std::string> opvar, \
                            const std::string & otherop, \
                            std::string other_opvar,\
                            const std::string & scqueueop);
    
    std::map<int, std::string> select_direct_Bottom_com_order(
                                const std::string & tablename, \
                                const std::string & op, \
                                std::map<std::string, std::string> opvar, \
                                const std::string & otherop, \
                                std::map<std::string, std::string> other_opvar, \
                                const std::string & orderop, \
                                std::string order_opvar,\
                                const std::string & scqueueop);

    std::map<int, std::string> update_direct_Bottom_compare(
                            const std::string &tablename, \
                            std::map<std::string, std::string> upvar, \
                            const std::string &op, \
                            std::map<std::string, std::string> opvar, \
                            const std::string & otherop, \
                            std::map<std::string, std::string> other_opvar);
};

#endif /* _DATA_ACCESS_LAYER_HEADER_H_ */
