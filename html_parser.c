#include "html_parser.h"
#include "state.h"

static int is_bom(const char* str_p, unsigned int bom)
{
    const char* digit_p = (char*)&bom;
    int i = 0;
    while(i < BOM_SIZE && *digit_p){
        if( str_p[i] != *digit_p ){
            break;
        }
        i++;
        digit_p++;
    }

    if(i < BOM_SIZE && *digit_p){
        return 0;
    }
    return 1;
}

static int bom_parser(const char* bom_p)
{
    if(is_bom(bom_p, UTF_8_BOM)){
        return CODE_UTF_8;
    }
    else if(is_bom(bom_p, UTF_16_L_BOM)){
        return CODE_UTF_16_L;
    }
    else if(is_bom(bom_p, UTF_16_B_BOM)){
        return CODE_UTF_16_B;
    }

    return 0;
}


static void skip_space(char **str_pp)
{
    while(isspace(**str_pp)){
        *str_pp++;
    }
}

static void add_to_name(char* key_p, char* src)
{
    if(!src or !key_p){
        return;
    }

    //拷贝*src的当前字节到key_p最后
    if(strlen(key_p) + 2

static bool get_attr_key(const char* p_str, char **key)
{
    char* name_p = p_str;

    char* key_p = (char*)malloc(BUFF_MAX);
    memset(key_p, 0, BUFF_MAX);

    int attr_name_state = 0;
    AttrNameStatus state = ATTR_NAME_INIT;

    while((state != ATTR_NAME_END or state != ATTR_NAME_STOP) && name_p){

        switch(state){
            case ATTR_NAME_INIT:
                {
                    if(isspace(*name_p)){
                        break;
                    }

                    //如果开头就碰到 '=' 号，则按照名称一部分处理
                    //开头遇到'>'的情况，在上一层中已经过滤掉，所以不用考虑
                    add_to_name(key_p, name_p);
                    state = ATTR_NAME_COPY;
                    break;
                }
            case ATTR_NAME_COPY:
                {
                    if(isspace(*name_p)){
                        break;
                    }
                    else if(is_value(*name, EQUEL)){
                        state = ATTR_NAME_END;
                        break;
                    }
                    else if(is_value(*name, TAG_SLANT) or  is_value(*name, TAG_END)){
                        state = ATTR_NAME_STOP;
                        break;
                    }

                    add_to_name(key_p, name_p);

                }
            case ATTR_NAME_STOP:
                {
                    //此时的key存在，但是value必定为空，通知上层无须继续
                    return true;
                }
            case ATTR_NAME_END:
                {
                    //此时的*name必定为'='
                    return false;
                }
            }
        name++;
    }





/*
 * 分析a_str字符串包含的属性key - value值
 * 并且插入链表头
 */
static HashList* parse_attribute(HashList const * attr_list, const char* a_str)
{
    char* p_str = a_str;
    char *key, *value;
    bool need_stop = false;

    AttrStatus  state = ATTR_INIT;

    while(p_str && (state != ATTR_END or state != ATTR_ABORT)){

        switch(state){
            case ATTR_INIT:
                {
                    if(is_value(*p_str, TAG_END)){
                        state = ATTR_ABORT;
                        break;
                    }
                    if(isspace(*p_str) or is_value(*p_str, TAG_SLANT)){
                        break;
                    }
                    state = ATTR_NAME;
                    break;
                }

            case ATTR_NAME:
                {
                    need_stop = get_attr_key(p_str, &key);
                    if(need_stop){
                        state = ATTR_END;
                        break
                    }
                    state = ATTR_EQUEL;
                    break;
                }

            case ATTR_EQUEL:
                {
                    skip_space(&p_str);
                    if(!is_value(*p_str, EQUEL) or !key){
                        state = ATTR_ABORT;
                        break;
                    }

                    state = ATTR_VALUE;
                    break;
                }
            case ATTR_VALUE:
                {
                    skip_space(&p_str);
                    // '>'
                    if(is_value(*p_str, TAG_END)){
                        state = ATTR_ABORT;
                        break;
                    }

                    value = get_attr_value(p_str);
                    state = ATTR_END;
                    break;
                }
            default:
                break;
        }
        p_str++;
    }

    if(state == ATTR_END && add_node(attr_list, key, value)){
        return attr_list;
    }

    if(key){
        free(key);
    }
    if(value){
        free(value);
    }
    return NULL;
}


static void get_charset(const char* page)
{
    charset_state parser_state = STATA_INIT;

    char* p = page;

    /*
    while(p){

        switch(parser_state){
            case STATE_INIT:
                {
                    pass;
                }
            case STATE_LESS_THEN:
                {
                    pass;
                }
            case 
    */
}


int html_parser(char* page)
{
    char bom_p[5] = {0};
    int bom_t;

    memcpy(bom_p, page, BOM_SIZE);
    if(bom_t = bom_parser(bom_p)){
        return bom_t;
    }
    else{
        get_charset(page);
        return 0;
    }
}
