//words_numbers Include Library.
sget_word: 
  STRING sdisp_one
  string stext 
  string sdec_points
  number sdigits 
  indicator sdecimals 
  indicator stens
  indicator shundreds 
  indicator sthousands
  indicator st_thousands
  indicator sh_thousands
  indicator smillions
  indicator st_millions
  indicator sh_millions
  indicator sjump
   
  indicate stens false
  indicate shundreds false
  indicate sthousands false
  indicate st_thousands false
  indicate sh_thousands false
  indicate smillions false
  indicate st_millions false
  indicate sh_millions false
  indicate sdecimals false 
  indicate sjump false
   
  right numb to sdigits 5 
  if sdigits gt 0.99 indicate stens true 
  right numb to sdigits 6  
  if sdigits gt 99.99 indicate shundreds true 
  right numb to sdigits 7 
  if sdigits gt 999.99 indicate sthousands true 
  right numb to sdigits 8 
  if sdigits gt 9999.99 indicate st_thousands true 
  right numb to sdigits 9 
  if sdigits gt 99999.99 indicate sh_thousands true 
  right numb to sdigits 10 
  if sdigits gt 999999.99 indicate smillions true 
  right numb to sdigits 11 
  if sdigits gt 9999999.99 indicate st_millions true 
  right numb to sdigits 12  
  if sdigits gt 99999999.99 indicate sh_millions true 
  move "" to word_1
  move 0 to sdigits 

  
sh_m:
  [sh_millions] begin
     mid numb to sdigits 1 1 
     gosub sh_word_1
     move stext to word_1
     if sdigits eq 1 begin
       if NOT [st_millions] begin
         if NOT [smillions] move "cien" to word_1
       end
     end  
     if NOT [st_millions] begin  
        if NOT [smillions] append word_1 " millones" 
     end 
   end 

st_m:
  [st_millions] begin
     mid numb to sdigits 2 2 
     gosub sa_word
     trim word_1 to word_1 
     if sdigits eq 1 begin
       append word_1 " " stext " mill¢n"
     end
     else begin
       append word_1 " " stext " millones"
     end
     goto sh_t // to avoid getting millions twice!
  end

sm:
  [smillions] begin
     mid numb to sdigits 1 3  
     gosub sa_word
     if sdigits eq 1 begin
       if NOT [sh_millions] begin
         if NOT [st_millions] move "un" to stext
       end
       append word_1 " " stext " mill¢n" 
     end
     else begin
       append word_1 " " stext " millones" 
     end
  end

sh_t:
  [sh_thousands] begin
     mid numb to sdigits 1 4 
     gosub sh_word_1
     if NOT [st_thousands] begin  
       if NOT [sthousands] MOVE "cien" TO stext
     END
     append word_1 " " stext 
     if NOT [st_thousands] begin  
       if NOT [sthousands] begin
         append word_1 " mil" 
         goto sh 
       end 
     end 
   end


st_t:
  [st_thousands] begin
     mid numb to sdigits 2 5 
     gosub sa_word
     [sh_millions] indicate sjump true
     [smillions]   indicate sjump true
     [st_millions] indicate sjump true
     [sh_thousands] indicate sjump true
     [sjump] begin
//       append word_1 " AND"
     end 
       append word_1 " " stext " mil"
     goto sh
   end
st:
   [sthousands] begin   
     mid numb to sdigits 1 6 
     gosub sa_word
     MOVE "N" TO sdisp_one
     [sh_millions]  MOVE "Y" TO sdisp_one
     [st_millions]  MOVE "Y" TO sdisp_one  
     [smillions]    MOVE "Y" TO sdisp_one  
     [sh_thousands] MOVE "Y" TO sdisp_one 
     [st_thousands] MOVE "Y" TO sdisp_one 
     IF sdisp_one NE "Y" BEGIN
       IF sdigits eq 1 move "" TO stext
     END
     if sdigits gt 0 begin
       append word_1 " " stext " mil" 
     end
     else begin
       append word_1 " mil" 
     end
   end 

sh:
  [shundreds] begin
     mid numb to sdigits 1 7 
     gosub sh_word_1
     append word_1 " " stext  
   end

sts:
  [stens] begin
     mid numb to sdigits 2 8 
     gosub sa_word
     [sh_millions] indicate sjump true
     [st_millions] indicate sjump true
     [smillions]   indicate sjump true
     [sh_thousands] indicate sjump true
     [st_thousands] indicate sjump true
     [sthousands]  indicate sjump true
     [shundreds]   indicate sjump true
//     [sjump] append word_1 " AND"
     append word_1 " " stext
   end 

sdec: 
   begin
     mid numb to sdigits 2 11 
     if sdigits gt 0 begin
       append word_1 " coma "
       mid numb to sdec_points 2 11
       append word_1 sdec_points
     end
     else begin 
       append word_1 " ===="  
     end
   end 
return 

sa_word:
move "" to stext
if sdigits gt 90 goto sa_word_91
if sdigits gt 80 goto sa_word_81
if sdigits gt 70 goto sa_word_71
if sdigits gt 60 goto sa_word_61
if sdigits gt 50 goto sa_word_51
if sdigits gt 40 goto sa_word_41
if sdigits gt 30 goto sa_word_31
if sdigits gt 20 goto sa_word_21
if sdigits gt 10 goto sa_word_11

IF sdigits EQ 1 MOVE "uno" TO stext
IF sdigits EQ 2 MOVE "dos" TO stext
IF sdigits EQ 3 MOVE "tres" TO stext
IF sdigits EQ 4 MOVE "cuatro" TO stext
IF sdigits EQ 5 MOVE "cinco" TO stext
IF sdigits EQ 6 MOVE "seis" TO stext
IF sdigits EQ 7 MOVE "siete" TO stext
IF sdigits EQ 8 MOVE "ocho" TO stext
IF sdigits EQ 9 MOVE "nueve" TO stext
IF sdigits EQ 10 MOVE "diez" TO stext
IF stext NE "" RETURN
sA_WORD_11:
IF sdigits EQ 11 MOVE "once" TO stext
IF sdigits EQ 12 MOVE "doce" TO stext
IF sdigits EQ 13 MOVE "trece" TO stext
IF sdigits EQ 14 MOVE "catorce" TO stext
IF sdigits EQ 15 MOVE "quince" TO stext
IF sdigits EQ 16 MOVE "dieciseis" TO stext
IF sdigits EQ 17 MOVE "diecisiete" TO stext
IF sdigits EQ 18 MOVE "dieciocho" TO stext
IF sdigits EQ 19 MOVE "diecinueve" TO stext
IF sdigits EQ 20 MOVE "veinte" TO stext
IF stext NE "" RETURN
sA_WORD_21:
IF sdigits EQ 21 MOVE "veintiuno" TO stext
IF sdigits EQ 22 MOVE "veintid¢s" TO stext
IF sdigits EQ 23 MOVE "veintitr‚s" TO stext
IF sdigits EQ 24 MOVE "veinticuatro" TO stext
IF sdigits EQ 25 MOVE "veinticinco" TO stext
IF sdigits EQ 26 MOVE "veintiseis" TO stext
IF sdigits EQ 27 MOVE "veintiseite" TO stext
IF sdigits EQ 28 MOVE "veintiocho" TO stext
IF sdigits EQ 29 MOVE "veintinueve" TO stext
IF sdigits EQ 30 MOVE "treinta" TO stext
IF stext NE "" RETURN
sA_WORD_31:
IF sdigits EQ 31 MOVE "treinta y uno" TO stext
IF sdigits EQ 32 MOVE "treinta y dos" TO stext
IF sdigits EQ 33 MOVE "treinta y tres" TO stext
IF sdigits EQ 34 MOVE "treinta y cuatro" TO stext
IF sdigits EQ 35 MOVE "treinta y cinco" TO stext
IF sdigits EQ 36 MOVE "treinta y seis" TO stext
IF sdigits EQ 37 MOVE "treinta y siete" TO stext
IF sdigits EQ 38 MOVE "treinta y ocho" TO stext
IF sdigits EQ 39 MOVE "treinta y nueve" TO stext
IF sdigits EQ 40 MOVE "cuarenta" TO stext
IF stext NE "" RETURN
sA_WORD_41:
IF sdigits EQ 41 MOVE "cuarenta y uno" TO stext
IF sdigits EQ 42 MOVE "cuarenta y dos" TO stext
IF sdigits EQ 43 MOVE "cuarenta y tres" TO stext
IF sdigits EQ 44 MOVE "cuarenta y cuatro" TO stext
IF sdigits EQ 45 MOVE "cuarenta y cinco" TO stext
IF sdigits EQ 46 MOVE "cuarenta y seis" TO stext
IF sdigits EQ 47 MOVE "cuarenta y siete" TO stext
IF sdigits EQ 48 MOVE "cuarenta y ocho" TO stext
IF sdigits EQ 49 MOVE "cuarenta y nueve" TO stext
IF sdigits EQ 50 MOVE "cincuenta" TO stext
IF stext NE "" RETURN
sA_WORD_51:
IF sdigits EQ 51 MOVE "cincuenta y uno" TO stext    
IF sdigits EQ 52 MOVE "cincuenta y dos" TO stext     
IF sdigits EQ 53 MOVE "cincuenta y tres" TO stext    
IF sdigits EQ 54 MOVE "cincuenta y cuatro" TO stext  
IF sdigits EQ 55 MOVE "cincuenta y cinco" TO stext   
IF sdigits EQ 56 MOVE "cincuenta y seis" TO stext    
IF sdigits EQ 57 MOVE "cincuenta y siete" TO stext   
IF sdigits EQ 58 MOVE "cincuenta y ocho" TO stext    
IF sdigits EQ 59 MOVE "cincuenta y nueve" TO stext   
IF sdigits EQ 60 MOVE "sesenta" TO stext
IF stext NE "" RETURN
sA_WORD_61:
IF sdigits EQ 61 MOVE "sesenta y uno" TO stext
IF sdigits EQ 62 MOVE "sesenta y dos" TO stext
IF sdigits EQ 63 MOVE "sesenta y tres" TO stext
IF sdigits EQ 64 MOVE "sesenta y cuatro" TO stext
IF sdigits EQ 65 MOVE "sesenta y cinco" TO stext
IF sdigits EQ 66 MOVE "sesenta y seis" TO stext
IF sdigits EQ 67 MOVE "sesenta y siete" TO stext
IF sdigits EQ 68 MOVE "sesenta y ocho" TO stext
IF sdigits EQ 69 MOVE "sesenta y nueve" TO stext
IF sdigits EQ 70 MOVE "setenta " TO stext
IF stext NE "" RETURN
sA_WORD_71:
IF sdigits EQ 71 MOVE "setenta y uno" TO stext
IF sdigits EQ 72 MOVE "setenta y dos" TO stext    
IF sdigits EQ 73 MOVE "setenta y tres" TO stext   
IF sdigits EQ 74 MOVE "setenta y cuatro" TO stext 
IF sdigits EQ 75 MOVE "setenta y cinco" TO stext  
IF sdigits EQ 76 MOVE "setenta y seis" TO stext   
IF sdigits EQ 77 MOVE "setenta y siete" TO stext  
IF sdigits EQ 78 MOVE "setenta y ocho" TO stext   
IF sdigits EQ 79 MOVE "setenta y nueve" TO stext  
IF sdigits EQ 80 MOVE "ochenta" to stext
IF stext NE "" RETURN
sA_WORD_81:
IF sdigits EQ 81 MOVE "ochenta y uno" TO stext
IF sdigits EQ 82 MOVE "ochenta y dos" TO stext
IF sdigits EQ 83 MOVE "ochenta y tres" TO stext     
IF sdigits EQ 84 MOVE "ochenta y cuatro" TO stext  
IF sdigits EQ 85 MOVE "ochenta y cinco" TO stext    
IF sdigits EQ 86 MOVE "ochenta y seis" TO stext     
IF sdigits EQ 87 MOVE "ochenta y siete" TO stext    
IF sdigits EQ 88 MOVE "ochenta y ocho" TO stext     
IF sdigits EQ 89 MOVE "ochenta y nueve" TO stext    
IF sdigits EQ 90 MOVE "noventa" to stext
IF stext NE "" RETURN
sA_WORD_91:
IF sdigits EQ 91 MOVE "noventa y uno" TO stext   
IF sdigits EQ 92 MOVE "noventa y dos" TO stext   
IF sdigits EQ 93 MOVE "noventa y tres" TO stext   
IF sdigits EQ 94 MOVE "noventa y cuatro" TO stext 
IF sdigits EQ 95 MOVE "noventa y cinco" TO stext  
IF sdigits EQ 96 MOVE "noventa y seis" TO stext   
IF sdigits EQ 97 MOVE "noventa y siete" TO stext  
IF sdigits EQ 98 MOVE "noventa y ocho" TO stext   
IF sdigits EQ 99 MOVE "noventa y nueve" TO stext  
RETURN                 
 
sH_WORD_1:
IF sdigits EQ 1 MOVE "ciento" TO stext
IF sdigits EQ 2 MOVE "doscientos" TO stext
IF sdigits EQ 3 MOVE "trescientos" TO stext     
IF sdigits EQ 4 MOVE "cuatrocientos" TO stext  
IF sdigits EQ 5 MOVE "quinientos" TO stext    
IF sdigits EQ 6 MOVE "seiscientos" TO stext     
IF sdigits EQ 7 MOVE "setecientos" TO stext    
IF sdigits EQ 8 MOVE "ochocientos" TO stext     
IF sdigits EQ 9 MOVE "novecientos" TO stext    
IF stext NE "" RETURN


