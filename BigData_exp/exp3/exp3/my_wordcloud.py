from wordcloud import WordCloud as wordcloud
import matplotlib.pyplot as plt
import my_count


# Generate WordCloud
def gen_wordcloud():
    my_count.count(my_count.schooltimes, my_count.schooltypestimes,
                   my_count.schooltimes_list, my_count.schooltypestimes_list)

    school_dict = {}
    other_count = 0
    for (school, times), i in zip(my_count.schooltimes_list, range(999)):
        if i < 300:
            school_dict[school] = times
        else:
            other_count += times
    school_dict['其他'] = other_count

    print(school_dict)

    # [ERROR]: Dont know why not show the image!!
    image = plt.imread(r'my_wordcloud_template.png')  # import image

    my_wordcloud = wordcloud(font_path=r'C:\Windows\Fonts\simfang.ttf', background_color='black',
                             max_font_size=100, max_words=500, mask=image, random_state=50)

    # Creat WordCloud
    my_wordcloud.generate_from_frequencies(school_dict)
    plt.imshow(my_wordcloud)
    plt.axis('off')
    plt.show()

    # Save the WordCloud
    my_wordcloud.to_file(r'my_wordcloud.png')


def main():
    gen_wordcloud()


if __name__ == '__main__':
    main()
