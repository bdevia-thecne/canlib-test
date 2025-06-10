import csv
import json

csv_filename = "/home/benja/Descargas/Diccionario_CANbus_ADAQ.csv"  
json_filename = "/home/benja/Escritorio/Thecne/dmh_blasthole_drills_sadp/Program/config/canbus/J1939_Thecne.json"

messages = {}

with open(csv_filename, mode="r", encoding="utf-8") as csvfile:
    reader = csv.DictReader(csvfile, delimiter=";")
    headers = next(reader)  

    for row in reader:
        pgn = row["PGN"]
        name = row["Name"]
        is_extended_frame = row["is_extended"].strip().lower() == "x"
        is_fd = row["is_fd"].strip().lower() == "x"

        if pgn not in messages:
            messages[pgn] = {
                "id": int(pgn),
                "name": name,
                "is_extended_frame": is_extended_frame,
                "is_fd": is_fd,
                "signals": []
            }
        is_big_endian = row["is_big_endian"].strip().lower() == "x"
        is_signed = row["is_signed"].strip().lower() == "x"
        is_float = row["is_float"].strip().lower() == "x"
        factor = row["factor"].replace(",", ".")
        signal = {
            "name": row["Signal"],
            "clase": row["Class"],
            "is_big_endian": is_big_endian,
            "is_signed": is_signed,
            "is_float": is_float,
            "factor": factor,
            "offset": row["offset"],
            "start_bit": int(row["start_bit"]),
            "bit_length": int(row["bit_length"])
        }
        messages[pgn]["signals"].append(signal)
    
    
data = {
    "messages": list(messages.values())
}

with open(json_filename, mode="w", encoding="utf-8") as jsonfile:
    json.dump(data, jsonfile, indent=4, ensure_ascii=False)

print(f"Archivo {json_filename} generado correctamente.")

#iconv -f ISO-8859-1 -t UTF-8 data/102PC001.csv -o data/102PC001_utf8.csv
#iconv -f US-ASCII -t UTF-8 data/102PC001.csv -o data/102PC001_utf8.csv