// https://wocota.hatenadiary.org/entry/20090628/1246188338
/* __asm__ ( asm template
 *  : output operand
 *  : input operand
 *  : work register);
 */

/* テンプレートは改行で複数行記述可能.(\tは可読性のためのおまけ)
 * %0: y, %1: x
 * =r, r: operand restrict
 *  制約文字 r: gccが任意のレジスタを割り当て変数への書き込み, 読み込みに利用
 *  制約修飾子 =: 書き込み専用 (default: read only)
 * x, y: variable
 * eax: work register: input/outputオペランドリスト以外のレジスタを使う場合, そのレジスタの使用法をgccに通知. 退避処理を挿入してくれる. input, outputオペランドに割り当て不可で自由に利用可能(アセンブラ中で)
 *
 * マッチング制約
 *  input operand の制約文字に数字を利用(指定のオペランドと同一のレジスタを使用)
 *  制約修飾子 "+" でも記述可能
 * &: 早期破壊オペランド 入力オペランドのレジスタを使わない出力オペランド
 * m: 直接メモリを参照
 __asm__("mov eax, %1\n\t"
 "mov %0, eax\n\t"
 : "=r" (y)
 : "r" (x)
 : "eax"
 );
 */

#ifdef MACOS
  #define SYS_WRITE 0x2000004
#else
  #define SYS_WRITE 1
#endif

/*__inline__ gccがこの関数を呼び出し元に展開する
 * __volatile__ 最適化の対象外とする
 *
 * cld: Direction FlagをClear, esi, ediなどが自動でインクリメントされるようになる
 * rep: rcxカウンタの数だけ繰り返し実行
 * movsd: esi -> edi にdouble word(4B) mov
 *    4B区切りで一気にコピー, 残りは3B以下
 * test $2, %4: 2とn/4の論理積計算後EFLAGSをセット結果が0ならZF: on
 * movsw: esi -> edi にsingle word(2B) mov
 *    nの2bit目が1(4で割って2以上余る)なら2Bコピー
 *
 * AT&T記法では定数には$をつけ, レジスタには%(inline時はエスケープのため%%)をつける
 *
 * %nはn番目のオペランド
 * ecxは初期値n/4, デクリメントするため書き込み可とするため
 * rdiは初期値dest, インクリメントするため書き込み可とするため(esiも同様)
 * nは読み込みしかしないため"r"で十分
 * memoryは, destの指すメモリに書き込むため必要
 */
static __inline__ void *memcpy(void *dest, const void *src, unsigned int n) {
  int d0, d1, d2; // dummy
  __asm__ __volatile__(
      "cld        \n\t"
      "rep movsd  \n\t"
      "test $2, %4 \n\t"
      "je 1f      \n\t"
      "movsw      \n"
      "1:         \t"
      "test $1, %4 \n\t"
      "je 2f      \n\t"
      "movsb      \n"
      "2:         \t"
      : "=&c" (d0), "=&D" (d1), "=&S" (d2)
      : "0" (n/4), "r" (n), "1" ((long) dest), "2" ((long) src)
      : "memory"
      );

  return dest;
}

static __inline__ int write(int fd, const char*str, unsigned int n) {
  int ret;
  __asm__ __volatile__(
      "syscall\t"
      : "=&a" (ret)
      : "d" (n), "S" (str), "D" (fd), "0" (SYS_WRITE)
      :
      );
  return ret;
}

int main() {
  char src_string[] = "hello world\n";
  char buff[32];

  if (sizeof(src_string) < sizeof(buff)) {
    memcpy(buff, src_string, sizeof(src_string));
    write(1, buff, __builtin_strlen(buff) + 1);
  } else
    write(1, "Error\n", 7);

  return 0;
}
