def main():
    file = input("File: ").strip(" ").lower()
    if ".gif" in file:
        mediatype = "image/gif"
    elif ".jpg" in file or ".jpeg" in file:
        mediatype = "image/jpeg"
    elif ".png" in file:
        mediatype = "image/png"
    elif ".pdf" in file:
        mediatype = "application/pdf"
    elif ".txt" in file:
        mediatype = "text/plain"
    elif ".zip" in file:
        mediatype = "application/zip"
    else:
        mediatype = "application/octet-stream"

    print(mediatype)


main()
